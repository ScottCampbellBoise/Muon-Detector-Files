# Muon-Detector-Files

This repository contains all the files used to develop, create, and test our version of the cosmic ray muon detector

--------------------------------------------------------------------------------------------------------------------
Description of Files:

•Cosmic-Ray-Detector-Materials_List.xlxs
  This file contains a spreadsheet with all the relevent information regarding the electrical components necessary 
  to build the detector described. It should be noted that thes list contains the appropriate parts, but not 
  necessarily the cheapest places to acquire said parts

•detector_circuit_color.png
  This is an image showing the detector circuit as we built it.

•Alpha_Isolation Teensy 3.6 Program File/Alpha_Isolation.ino
  This is program file written for Arduino/Teensy. To download the necessary IDE to open this file, visit 
  https://www.arduino.cc/en/Main/Software. This file is used for our calibration of the detector with the alpha source.

•Cosmic_Ray_Isolation Teensy 3.6 Program File/Cosmic_Ray_Isolation.ino
  This is a program file written for Arduino/Teensy. This file is used to isolate cosmic ray muons by stacking two 
  detector units vertcally.
  
•Muon-Detector-Files/Muon_Detector_Data_Recorder.pde
  This is a program file written in the Processing Language. To download the necessary IDE to open this file, visit 
  https://processing.org/download/. This file reads data from the Teensy and records it to a .txt file through a USB 
  serial connection
  
--------------------------------------------------------------------------------------------------------------------
