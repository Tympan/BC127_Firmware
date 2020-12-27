BC127_Firmware
===========================

**Purpose**: The BC127 is the bluetooth module used in Tympan RevD and RevE.  This repository contains information and tools relating to the firmware on those devices.

**History**: Most of the Tympan RevD units were shipped with BC127 modules that came from the original vendor with the "V5" version of the Melody firmware.  While developing the Tympan RevE, we found that the BC127 modules came from original vendor with "V6" version of the firmware.  While figuring out how to change the firmware, we found that a newer "V7" version was also available.  Using the tool in this repo, any version of the BC127 can be changed to any other version.

** Instructions**: 

First, download this repository.

Second, load your Tympan with the correct sketch to enable updating of the BC127 firmware:
    1) From "Arduino", open the sketch "BC127_Firmware_Updater" in the Arduino IDE
    2) At the top of the sketch, depending upon whether you have a Tympan RevD or RevE, enable the correct portion of the code
    3) Compile and upload to your Tympan
    4) Under the Arduino's "Tools" menu, note the COM port for your Tympan
    5) Close any SerialMonitor that you might have open
	
Third, install and use the firmware updater tool
    1) From "Firmware Updater Tool", unzip "BlueSuite_2_6_6_1311.zip" and install
	2) Run "DfuWizard.exe"
	3) When running, Choose "Next" and then choose "COM Port" and then choose the COM Port for your Tympan.  Hit "Next".
	4) Choose either of the first two radio buttons.  The second one "Download a new version of the firmware, without first saving a copy of the current version." will be faster.  Hit "Next".
	5) Hit the "Browse" button and find "BC127 Firmware Versions" in this repo and select the Melody firmware version that you want.
	6) Hit "Next" to start the Firmware update process.  It will take many minutes.

