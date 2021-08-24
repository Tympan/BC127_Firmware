/*
 * BC127_Firmware_Updater
 * 
 * Created: Chip Audette, OpenAudio, Nov-Dec 2020
 * 
 * Purpose: Setup the Tympan (RevD, RevE) so that it can relay text from its BC127 bluetooth
 *          module to the host PC so that the PC can update the firmware on the BC127
 *          
 * Use this echo program with the "DfuWizard" that comes with BlueSuite 2.6.6
 * 
 * The trick is that the BT UART must be increased in speed (and changed parity?) 
 *         when in DFU mode.  That's crazy.
 *          
 * Open Source via MIT License.  Use at your own risk.         
 */
 
usb_serial_class *USB_Serial = &Serial;
HardwareSerial *BT_Serial = &Serial1;
//#define RTS_PIN 18  //Chosen by WEA
//#define CTS_PIN 19  //for Serial3
#if 1  //set to 1 for RevE or set to 0 for RevD
  //Tympan RevE
  #define BT_REGEN 14 //from Tympan RevE
  #define BT_RESET 9  //from Tympan RevE
  #define BT_PIO0 5   //from Tympan RevE
  #define BT_PIO5 2   //from Tympan RevE
#else
  //Tympan RevD
  #define BT_REGEN 31 //from Tympan RevD
  #define BT_RESET 35  //from Tympan RevD
  #define BT_PIO0 56   //from Tympan RevD
  #define BT_PIO5 33   //from Tympan RevD
#endif
String response, given_BT_name, BT_hex;
 
void echoIncomingUSBSerial(void) {
  while (USB_Serial->available()) {
    BT_Serial->write(USB_Serial->read()); //echo messages from USB Serial over to BT Serial
  }
}
 
void echoIncomingBTSerial(void) {
  while (BT_Serial->available()) {
    USB_Serial->write(BT_Serial->read());//echo messages from BT serial over to USB Serial
  }
}
 
void setup() {
  
  //setup BT Regen
  delay(100);
  pinMode(BT_REGEN,OUTPUT);digitalWrite(BT_REGEN,HIGH); //pull high for normal operation
  delay(10);  digitalWrite(BT_REGEN,LOW); //hold at least 5 msec, then return low
 
  //setup BT Resent
  pinMode(BT_RESET,OUTPUT);
  digitalWrite(BT_RESET,LOW);delay(10); //reset the device
  digitalWrite(BT_RESET,HIGH);  //normal operation.
  
  // Start the serial ports on the Tympan
  USB_Serial->begin(115200); 
  BT_Serial->begin(9600);
 
  //clear the buffer
  delay(1000);
  BT_Serial->print("HELP");BT_Serial->print('\r');delay(500); echoIncomingBTSerial();
  BT_Serial->print('\r'); BT_Serial->flush();  BT_Serial->print('\r');delay(500); echoIncomingBTSerial();
 
  //enter DFU mode
  BT_Serial->print("DFU");BT_Serial->print('\r');BT_Serial->flush(); delay(500); echoIncomingBTSerial();
 
  // change baud rate...this is the tricky bit that is required by DFU mode!
  BT_Serial->clear();  //clear the incoming buffer
  BT_Serial->end();    //stop the slower serial
  BT_Serial->begin(115200,SERIAL_8E1);  // https://sierrawireless.trydiscourse.com/t/bc127-manual-firmware-update-bc127/13211
  
}
 
// Arduino loop() function, which is run over and over for the life of the device
void loop() {
  echoIncomingUSBSerial();     //echo messages from USB Serial over to BT Serial
  echoIncomingBTSerial();  //echo messages from BT serial over to USB Serial
} //end loop();
 
