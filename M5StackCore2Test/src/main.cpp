/****************************************************************************************	
**  This is example LINX firmware for use with the Arduino Uno with the serial 
**  interface enabled.
**
**  For more information see:           www.labviewmakerhub.com/linx
**  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
**  
**  Written By Sam Kristoff
**
**  BSD2 License.
****************************************************************************************/

//Include All Peripheral Libraries Used By LINX
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>

// Compiler switches
#define LINX_DEVICE_FAMILY   2

//Include Device Specific Header From Sketch>>Import Library (In This Case LinxChipkitMax32.h)
//Also Include Desired LINX Listener From Sketch>>Import Library (In This Case LinxSerialListener.h)
#include <M5Core2.h>
#include <LinxM5Core2.h>
#include <LinxSerialListener.h>
//Create A Pointer To The LINX Device Object We Instantiate In Setup()
LinxM5Core2* pLinxDevice;

unsigned long actualBandWidth;
//Initialize LINX Device And Listener
void setup()
{
  //Instantiate The LINX Device
  M5.begin(true,false,true,false,kMBusModeInput);
  
  pLinxDevice = new LinxM5Core2();
  pLinxDevice->UartSetBaudRate(0,9600,&actualBandWidth);
  M5.lcd.println(actualBandWidth,0);
  //pLinxDevice->EnableDebug(DEBUG_ENABLED);
  //The LINXT Listener Is Pre Instantiated, Call Start And Pass A Pointer To The LINX Device And The UART Channel To Listen On
  LinxSerialConnection.Start(pLinxDevice, 0);  
  
}

void loop()
{
  //Listen For New Packets From LabVIEW
  LinxSerialConnection.CheckForCommands();
  delay(10);
  //Your Code Here, But It will Slow Down The Connection With LabVIEW
  M5.Lcd.print(".");
  
}

