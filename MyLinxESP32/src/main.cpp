/****************************************************************************************
**  This is example LINX firmware for use with the ESP32 device
**
**  For more information see:           www.labviewmakerhub.com/linx
**  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
**
**  Written By Ken Sharp
**
**  BSD2 license.
****************************************************************************************/

//Include Device Specific Header From Sketch>>Import Library (In This Case LinxESP32.h)
//Also Include Desired LINX Listener From Sketch>>Import Library (In This Case LinxESP32WifiListener.h)
#include <LinxESP32.h>
#include <Arduino.h>
//Create A Pointer To The LINX Device Object We Instantiate In Setup()
LinxESP32* pLinxDevice;
//LinxESP32WifiListener* LinxWifiConnection;

//Initialize LINX Device And Listener
void setup()
{
  //Instantiate The LINX Device
  //LinxWifiConnection = new (LinxESP32WifiListener);
  pLinxDevice = new LinxESP32();
  pLinxDevice->EnableDebug(DEBUG_ENABLED);
  
  // PWM & Servo Setup
  uint8_t pwmList[] = {};         // Max16Ch {0, 26, ...}
  uint16_t pwmFrequency = 12000;  // LED:12000, Servo:50
  for (int i = 0; i < sizeof(pwmList); i++) {
    ledcSetup(i, pwmFrequency, 8);
    pinMode(pwmList[i], OUTPUT);
    ledcAttachPin(pwmList[i], i);
  }

  // I2C Begin ch0:Wire, ch1:Wire1
  //Wire.begin();
  //Wire1.begin(32, 33);

  // The LINX Listener Is Pre Instantiated.
  // Set SSID (Network Name), Security Type, Passphrase/Key, And Call Start With Desired Device IP and Port
  // If not set, it will connect with the last connection information
  //LinxWifiConnection.SetSsid("VI Technologies");
  //LinxWifiConnection.SetSecurity(WPA2_PASSPHRASE);  //NONE, WPA2_PASSPHRASE, WPA2_KEY, WEP40, WEO104
  //LinxWifiConnection.SetPassphrase("3942074321882926");

  LinxWifiConnection.SetSsid("PandaGrote");
  LinxWifiConnection.SetSecurity(WPA2_PASSPHRASE);  //NONE, WPA2_PASSPHRASE, WPA2_KEY, WEP40, WEO104
  LinxWifiConnection.SetPassphrase("Zbroggbvgw-1");

  //Start With Fixed Port.  When Using This Method You Cannot Update The Port Using LINX VIs
  LinxWifiConnection.Start(pLinxDevice, 44300);
  delay(1000);
  //pLinxDevice->EnableDebug(0);
  //LinxWifiConnection.PrintWifiInfo();
  pLinxDevice->EnableDebug(DEBUG_ENABLED);
}

void loop()
{
  //Listen For New Packets From LabVIEW
  LinxWifiConnection.CheckForCommands();

  //Your Code Here, But It will Slow Down The Connection With LabVIEW
  delay(100);
}
