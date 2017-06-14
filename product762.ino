#define RECV_OK 42
#define STATE_MSG_LEN 32 // 32 bytes (four times double float, each has 8 bytes) + 1 (direction flags byte) = 33
#define STRANGE_FACTOR // = 1000000 / 16 = 62500.00; 1000000 is the conversion seconds to µs; 1/16 is the strange factor
union unionStateFreq
{
  double doubleValues[4];
  byte byteValues[32];
} stateFreqsRead;
double stateFreqs[4];
int stateFreqsCurByte = 0;
byte stateDirectionFlags = 0; // all rotate right
double lastTimes[4];
int dirPins[4] = {0, 2, 4, 6};
int stepPins[4] = {1, 3, 5, 7};
byte logMasks[4] = {8, 4, 2, 1}; // start with DEC 8 = BIN 0000 1000, DEC 4 = 0000 0100, DEC 2 = 0000 0010, DEC 1 = 0000 0001;

void setup() {
  Serial.begin(9600);
  lastTimes[0] = lastTimes[1] = lastTimes[2] = lastTimes[3] = micros(); // init the last time var
  stateFreqs[0] = stateFreqs[1] = stateFreqs[2] = stateFreqs[3] = 0;
  stateFreqsRead.doubleValues[0] = stateFreqsRead.doubleValues[1] = stateFreqsRead.doubleValues[2] = stateFreqsRead.doubleValues[3] = 0;
  for(unsigned int i = 0; i < 4; i++)
  {
    pinMode(dirPins[i], OUTPUT);
    pinMode(stepPins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    if(stateFreqsCurByte < STATE_MSG_LEN) // bytes 0 - 31 (32) are the 4 floating point numbers
    {      
      stateFreqsRead.byteValues[stateFreqsCurByte] = Serial.read();
      stateFreqsCurByte++;
    } 
    else if(stateFreqsCurByte == STATE_MSG_LEN) // the 32rd (33rd) byte is  the direction flags
    {
      stateDirectionFlags = Serial.read();
      Serial.write(RECV_OK); // write recv ok
      updateDirAndFreq(); // update frequencies and directions  
      stateFreqsCurByte = 0;
    }
  }
  for(int i = 0; i < 4; i++)
  {
    if(micros() < lastTimes[i]) // micros will restart ~ every 71 minutes, if we yust stepped in this gap, simply restart
    {
       lastTimes[i] = micros();
    }
    else
    {
      if(((micros() - lastTimes[i]) * stateFreqs[i]) > 62500.0)
      {        
        lastTimes[i] = micros();
        digitalWrite(stepPins[i], 1); //step-pin on for 1 µs
        delayMicroseconds(1); //step-pin on for 1 µs
        digitalWrite(stepPins[i], 0); //step-pin on for 1 µs
      }
    }
  }
}

void updateDirAndFreq()
{
  for(unsigned int i = 0; i < 4; i++)
  {
    stateFreqs[i] = stateFreqsRead.doubleValues[i]; // update frequencies
    if((stateDirectionFlags & logMasks[i]) == logMasks[i]) // bit wise & the directions flags bit set is clockwise (left rotation)
    {
      digitalWriteFast(dirPins[i], 1); // rotate clockwise (left)
    }
    else
    {
      digitalWriteFast(dirPins[i], 0); // rotate counter clockwise (right)
    }
  }  
}

