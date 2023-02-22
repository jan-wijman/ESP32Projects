#include <Arduino.h>
#include <LinxSerialListener.h>

LinxSerialListener* MyDeviceListener;

MyDeviceListener = new LinxSerialListener();

void setup()
{
  // I2C Begin ch0:Wire, ch1:Wire1
  //Wire.begin();
  //Wire1.begin(32, 33);

  // The LINXT Listener Is Pre Instantiated, Call Start And Pass A Pointer To The LINX Device And The UART Channel To Listen On
  // ch0:Serial
  // ch1:Serial1
  // ch2:Serial2
  // ch3:SerialBT
  LinxSerialConnection.Start(DeviceM5Core2, 0);
}

void loop()
{
  //Listen For New Packets From LabVIEW
  LinxSerialConnection.CheckForCommands();

  //Your Code Here, But It will Slow Down The Connection With LabVIEW
  delay(1);
}
