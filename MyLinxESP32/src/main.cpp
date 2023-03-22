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
#define GO_FOR_WIFI


// List of custom commands for the ESP32
// First command is just as an example.
int myCustomCommand(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response);
int getAOResolution(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response);
int getAORef(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response);
int SetAO(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response);

//Create A Pointer To The LINX Device Object We Instantiate In Setup()
LinxESP32* pLinxDevice;

//Initialize LINX Device And Listener
void setup()
{
  //Instantiate The LINX Device
  pLinxDevice = new LinxESP32();
  pLinxDevice->EnableDebug(DEBUG_ENABLED);
  
  //PWM & Servo Setup
  //uint8_t pwmList[NUM_SPI_CHANS] = {0,1,2,3};         // Max16Ch {0, 26, ...}
  //uint16_t pwmFrequency = 12000;  // LED:12000, Servo:50
  //for (int i = 0; i < sizeof(pwmList); i++) {
  //  ledcSetup(i, pwmFrequency, 8);
  //  pinMode(pwmList[i], OUTPUT);
  //  ledcAttachPin(pwmList[i], i);
  //}

  // I2C Begin ch0:Wire, ch1:Wire1
  //Wire.begin();
  //Wire1.begin(32, 33);

  //The LINX Listener Is Pre Instantiated.
  //Set SSID (Network Name), Security Type, Passphrase/Key, And Call Start With Desired Device IP and Port
  //If not set, it will connect with the last connection information
  
  LinxWifiConnection.SetSsid("VI Technologies");
  LinxWifiConnection.SetSecurity(WPA2_PASSPHRASE);  //NONE, WPA2_PASSPHRASE, WPA2_KEY, WEP40, WEO104
  LinxWifiConnection.SetPassphrase("3942074321882926");

  //LinxWifiConnection.SetSsid("PandaGrote");
  //LinxWifiConnection.SetSecurity(WPA2_PASSPHRASE);  //NONE, WPA2_PASSPHRASE, WPA2_KEY, WEP40, WEO104
  //LinxWifiConnection.SetPassphrase("Zbroggbvgw-1");

  //Start With Fixed Port.  When Using This Method You Cannot Update The Port Using LINX VIs
  LinxWifiConnection.Start(pLinxDevice, 44300);
  pLinxDevice->EnableDebug(DEBUG_ENABLED);

  
  LinxWifiConnection.AttachCustomCommand(0, myCustomCommand);
  LinxWifiConnection.AttachCustomCommand(1, getAOResolution);
  LinxWifiConnection.AttachCustomCommand(2, getAORef);
  LinxWifiConnection.AttachCustomCommand(3, SetAO);

}

void loop()
{
  //Listen For New Packets From LabVIEW
  LinxWifiConnection.CheckForCommands();

  //Your Code Here, But It will Slow Down The Connection With LabVIEW
  
}

//
int myCustomCommand(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response)
{
   
  for(int i=0; i<numInputBytes; i++)
  {
    response[i] = input[i] +1;
  }
   
  *numResponseBytes = numInputBytes;
  pLinxDevice->DebugPrint("NrOfInputBytes: ") ; pLinxDevice->DebugPrintln(numInputBytes);
   
  return L_OK;
}
int getAOResolution(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response)
{
    response[0] = pLinxDevice->m_AoResolution;
    *numResponseBytes = 1;
    return L_OK;
}
int getAORef(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response)
{
    response[0] = ((pLinxDevice->m_AoRefSet >>24) & 0xFF);
    response[1] = ((pLinxDevice->m_AoRefSet >>16) & 0xFF);
    response[2] = ((pLinxDevice->m_AoRefSet >>8) & 0xFF);
    response[3] = ((pLinxDevice->m_AoRefSet) & 0xFF);
    *numResponseBytes = 4;

    return L_OK;
}
int SetAO(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response)
{
 char numChannels;
 unsigned char* channels; 
 unsigned char* values;
 
 numChannels = input[0];
 channels = &input[1];
 values = &input[1 + numChannels];
for(int i= 0; i<numChannels; i++)
{
  dacWrite( channels[i], (values[i]));
}

return L_OK;
}