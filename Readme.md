SPOClab-Syringe Pump Software for DropletKitchen Pumps
author: Christian Arrer; christianarrer@gmail.com

1.Introduction
This is a software to operate the DropletKitchen Syringe Pumps (https://github.com/DropletKitchen/pumpsn17). 
The software consists of two parts: The part runs on the Teensy Board (2.0/3.0) and the second part runs on Windows. 
The Teensy Board software is in �teensy/product762/product762.ino� as an Arduino file. 
The PC software is a Visual Studio Community 2017 Project and can be found inside �pc/prodcut762/product762.sln�.
Install the latest Arduino (https://www.arduino.cc/en/Main/OldSoftwareReleases) and Teensyduino 
(https://www.pjrc.com/teensy/td_download.html) on Windows.
Install Visual Studio Commmunity 2017 
(https://www.visualstudio.com/de/thank-you-downloading-visual-studio/?sku=Community&rel=15) and 
make sure to include all Visual C# features.

1.1	Compilation for Teensy Board
Start Arduino, go to �tools->board� and choose �Teensy 2.0� or �Teensy 3.0�, depending on which board you got. 
Then go to �sketch->upload� or press �ctrl-U� or press the �arrow button� to upload the code on your USB connected Teensy Board.

1.2	Compile Windows Software
Open up the Visual Studio Community 2017 C# IDE, then open the file �pc/prodcut762/product762.sln�. 
In the �Standard�/�Default� Menustrip 
Switch to compile for �Release�, this will strip the debug overhead from the executable. 
Then go to �build->rebuild solution�.  Now you should have a �porduct762.exe� in �pc\product762\bin\Release� folder. 
You can launch it on any PC with .NET Framework 4.6 installed.
