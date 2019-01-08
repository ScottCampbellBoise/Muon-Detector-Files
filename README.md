# Muon-Detector-Files

This repository contains all the files used to develop, create, and test our version of the cosmic ray muon detector

--------------------------------------------------------------------------------------------------------------------
Description of Files:

•Detector Materials List.xlxs
  This file contains a spreadsheet with all the relevent information regarding the electrical components necessary 
  to build the detector described. It should be noted that thes list contains the appropriate parts, but not 
  necessarily the cheapest places to acquire said parts

•Detector Circuit Outline.png
  This is an image showing the detector circuit as we built it.

•Arduino & Teensy/Alpha_Isolation.ino
  This is program file written for Arduino/Teensy. To download the necessary IDE to open this file, visit 
  https://www.arduino.cc/en/Main/Software. This file is used for our calibration of the detector with the alpha source.

•Arduino & Teensy/Cosmic_Ray_Isolation.ino
  This is a program file written for Arduino/Teensy. This file is used to isolate cosmic ray muons by stacking two 
  detector units vertcally.
  
•Processing/Muon_Detector_Data_Recorder.pde
  This is a program file written in the Processing Language. To download the necessary IDE to open this file, visit 
  https://processing.org/download/. This file reads data from the Teensy and records it to a .txt file through a USB 
  serial connection
  
--------------------------------------------------------------------------------------------------------------------


Suggestions for building the circuit:

    1) Plan out the circuit layout on your breadboard ahead of time, if you have access to one, use a solderless breadboard
       first, and once it works as expeted, move onto the more permanent solderable breadboard
    2) Build the circuit in stages: instead of creating the entire circuit and then debugging, it is often usefull to build a       
       circuit in stages, debugging after adding each stage. The article this detetor is described in details multiple stages
       that would be convinient to construct one at a time.
    3) This article, https://makezine.com/2009/01/12/surface-mount-soldering/, describes how to do surface mount soldering.
    4) Use appropriate current limiting power supplies: by current limiting a power supply, you restrict the maximum current
       your circuit can draw, this can save sensitive components, and ease headaches later on.
    5) For more tips and techniques for through-hole soldering: 
       https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering/all



Startup Guide:

  • For detecting cosmic rays:
  
    1) Connect the output of the top detector unit into the Teensy analog port A2
    2) Connect the output of the bottom detector unit into the Teensy analog port A3
    3) Open the Arduino app, and plug in the Teensy 3.6 with the micro-USB connector
    4) Under the tool bar, locate: Tools/Port/xxxx (Teensy 3.6) * xxxx will be the Serial port your Teensy is connected to *
    5) Open the file Processing/Muon_Detector_Data_Recorder.pde in the Processing App
    6) Change the line: mySerial = new Serial( this, "xxxx", 250000 ); * Substitute your port (xxxx) from #4 *
    7) Upoad the program Arduino & Teensy/Cosmic_Ray_Isolation.ino onto the Teensy Microcontroller.
    8) Within 5 seconds, run the Processing program. To quit, select the pop up box and press any key
    
