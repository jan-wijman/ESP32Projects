/****************************************************************************************
**  LINX ESP32 device code
**
**  For more information see:           www.labviewmakerhub.com/linx
**  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
**
**  Written By Ken Sharp
**
** BSD2 License.
****************************************************************************************/

/****************************************************************************************
**  Includes
****************************************************************************************/


#include "utility/LinxDevice.h"
#include "utility/LinxWiringDevice.h"
#include "LinxESP32.h"

/****************************************************************************************
**  Member Variables
****************************************************************************************/
//System
const unsigned char LinxESP32::m_DeviceName[DEVICE_NAME_LEN] = "ESP32";

//AI
// Only ADC 1 because of WiFi ADC2 does not work
const unsigned char LinxESP32::m_AiChans[NUM_AI_CHANS] = {36,37,38,39,32,33,34,35,4,0,2,15,13,12,14,27,25,26}; 
const unsigned long LinxESP32::m_AiRefIntVals[NUM_AI_INT_REFS] = {};
const int LinxESP32::m_AiRefCodes[NUM_AI_INT_REFS] = {};

//AO
const unsigned char LinxESP32::m_AoChans[NUM_AO_CHANS] = {25, 26}; // here is are pins
const unsigned char LinxESP32::m_AoResolution = AO_RES_BITS ;
const unsigned long LinxESP32::m_AoRefDefault = AO_REFV;
const unsigned long LinxESP32::m_AoRefSet = AO_REFV;
//None

//DIGITAL
// GPIO's 6, 7, 8, 9, 10, 11 are used by build in flash
const unsigned char LinxESP32::m_DigitalChans[NUM_DIGITAL_CHANS] = {0, 1, 2, 3, 4, 5, 12, 
                                                                      13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 
                                                                      ,26, 27, 28, 29, 30, 31 ,32, 33, 34, 35, 36, 37, 38, 39  };

//PWM
const unsigned char LinxESP32::m_PwmChans[NUM_PWM_CHANS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

//QE
//None

//SPI
const unsigned char LinxESP32::m_SpiChans[NUM_SPI_CHANS] = {0,1}; // VSPI, HSPI
unsigned long LinxESP32::m_SpiSupportedSpeeds[NUM_SPI_SPEEDS] = {8000000, 4000000, 2000000, 1000000, 500000, 250000, 125000};
int LinxESP32::m_SpiSpeedCodes[NUM_SPI_SPEEDS] = {SPI_CLOCK_DIV2, SPI_CLOCK_DIV4, SPI_CLOCK_DIV8, SPI_CLOCK_DIV16, SPI_CLOCK_DIV32, SPI_CLOCK_DIV64, SPI_CLOCK_DIV128};

//uninitalised pointers to SPI objects. They are declared in the .h file. But here they must be initialised. This to avoid linker problems.
SPIClass * LinxESP32::vspi = NULL;
SPIClass * LinxESP32::hspi = NULL;
   
//I2C
unsigned char LinxESP32::m_I2cChans[NUM_I2C_CHANS] = {0, 1};
unsigned char LinxESP32::m_I2cRefCount[NUM_I2C_CHANS];

//UART
unsigned char LinxESP32::m_UartChans[NUM_UART_CHANS] = {0, 1, 2, 3};
unsigned long LinxESP32::m_UartSupportedSpeeds[NUM_UART_SPEEDS] = {300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200};

//SERVO
const unsigned char LinxESP32::m_ServoChans[NUM_SERVO_CHANS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

/****************************************************************************************
**  Constructors /  Destructor
****************************************************************************************/
LinxESP32::LinxESP32()
{
  DeviceFamily = DEVICE_FAMILY ;
  DeviceId = 0x00;	//??
  DeviceNameLen = DEVICE_NAME_LEN;
  DeviceName =  m_DeviceName;

  //LINX API Version
  LinxApiMajor = 2;
  LinxApiMinor = 0;
  LinxApiSubminor = 0;

  //DIGITAL
  NumDigitalChans = NUM_DIGITAL_CHANS;
  DigitalChans = m_DigitalChans;

  //AI
  NumAiChans = NUM_AI_CHANS;
  AiChans = m_AiChans;
  AiResolution = AI_RES_BITS;
  AiRefSet = AI_REFV;

  AiRefDefault = AI_REFV;
  AiRefSet = AI_REFV;
  AiRefCodes = m_AiRefCodes;

  NumAiRefIntVals = NUM_AI_INT_REFS;
  AiRefIntVals = m_AiRefIntVals;

  AiRefExtMin = 0;
  AiRefExtMax = 5000000;

  //AO
  NumAoChans = NUM_AO_CHANS;
  AoChans = m_AoChans;
  AoResolution = m_AoResolution;
  AoRefDefault = m_AoRefDefault;
  AoRefSet = m_AoRefSet;
  
  //PWM
  NumPwmChans = NUM_PWM_CHANS;
  PwmChans = m_PwmChans;

  //QE
  NumQeChans = 0;
  QeChans = 0;


  //UART
  NumUartChans = NUM_UART_CHANS;
  UartChans = m_UartChans;
  UartMaxBaud = m_UartSupportedSpeeds[NUM_UART_SPEEDS - 1];
  NumUartSpeeds = NUM_UART_SPEEDS;
  UartSupportedSpeeds = m_UartSupportedSpeeds;

  //I2C
  NumI2cChans = NUM_I2C_CHANS;
  I2cChans = m_I2cChans;
  I2cRefCount = m_I2cRefCount;

  //SPI
  NumSpiChans = NUM_SPI_CHANS;
  SpiChans = m_SpiChans;
  NumSpiSpeeds = NUM_SPI_SPEEDS;
  SpiSupportedSpeeds = m_SpiSupportedSpeeds;
  SpiSpeedCodes = m_SpiSpeedCodes;
  vspi = &SPI; // SPIClass(VSPI)
  hspi = new SPIClass(HSPI); // SPIClass(HSPI)

  //CAN
  NumCanChans = 0;
  CanChans = 0;

  //SERVO
  NumServoChans = NUM_SERVO_CHANS;
  ServoChans = m_ServoChans;

  //If Debuging Is Enabled Call EnableDebug()
#if DEBUG_ENABLED >= 0
  EnableDebug(DEBUG_ENABLED);
#endif
}

int LinxESP32::AnalogSetRef(unsigned char mode, unsigned long voltage)
{
  // There are no user-accessible analog references on the ESP32
  return L_FUNCTION_NOT_SUPPORTED;
}

LinxESP32::~LinxESP32()
{

}

/****************************************************************************************
**  Functions
****************************************************************************************/
  SPIClass* LinxESP32::SPIChannel(unsigned char channel)
  {
    switch(channel)
    {
      case 0: {
        return vspi;
      }
        break;

      case 1: {
         return hspi;
      }
        break;

      default:{
        return NULL;
      }
      break;
    }
  }


int LinxESP32::SpiOpenMaster(unsigned char channel)
{
  DebugPrintln("In the OpenMaster method.");
  switch(channel)
  {
    case 0:
    {
      vspi->begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS); //SCLK, MISO, MOSI, SS
      pinMode(vspi->pinSS(), OUTPUT); //VSPI SS
      DebugPrintln("Channel 0 opened");
      
    }
    break;
    case 1: 
    {
      hspi->begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS); //SCLK, MISO, MOSI, SS
      pinMode(hspi->pinSS(), OUTPUT); //HSPI SS
      DebugPrintln("Channel 1 opened");
    }
    break;
    default:
    {
        DebugPrintln("Channel not opened");
      
    }
    break;
  }
  return 0;
}

int LinxESP32::SpiSetBitOrder(unsigned char channel, unsigned char bitOrder)
{
  
  SPIChannel(channel)->setBitOrder(bitOrder);
  return 0;
}

int LinxESP32::SpiSetMode(unsigned char channel, unsigned char mode)
{
  switch (mode)
  {
    case 0:
      SPIChannel(channel)->setDataMode(SPI_MODE0);
      break;
    case 1:
      SPIChannel(channel)->setDataMode(SPI_MODE1);
      break;
    case 2:
      SPIChannel(channel)->setDataMode(SPI_MODE2);
      break;
    case 3:
      SPIChannel(channel)->setDataMode(SPI_MODE3);
      break;
  }

  return 0;
}

int LinxESP32::SpiSetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed)
{
  //Loop Over All Supported SPI Speeds (SPI Speeds Should Be Fastest -> Slowest)
  for (int index = 0; index < NumSpiSpeeds; index++)
  {
    //If Target Speed Is greater or equal to the current supported speed use current supported speed (it's the fastest supported speed that is less or equal to the target)
    if (speed >= *(SpiSupportedSpeeds + index))
    {
      *actualSpeed = *(SpiSupportedSpeeds + index);
      SPIChannel(channel)->setClockDivider(*(SpiSpeedCodes + index));
      break;
    }
    if (index == NumSpiSpeeds - 1)
    {
      //Target speed is slower than slowest supported.  Use slowest supported
      *actualSpeed = *(SpiSupportedSpeeds + index);
      SPIChannel(channel)->setClockDivider(*(SpiSpeedCodes + index));
    }
  }

  return L_OK;
}

int LinxESP32::SpiWriteRead(unsigned char channel, unsigned char frameSize, unsigned char numFrames, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer)
{
  //Set CS Pin As DO
  pinMode(csChan, OUTPUT);

  //Set CS Pin Idle Before Starting SPI Transfer
  digitalWrite(csChan, (~csLL & 0x01) );

  //Loop Over Frames
  for (int i = 0; i < numFrames; i++)
  {
    //Start of frame, set CS Pin Active
    digitalWrite(csChan, (csLL & 0x01) );

    //Loop Over Bytes In Frame
    for (int j = 0; j < frameSize; j++)
    {
      //Transfer Data
      unsigned char byteNum = (i * frameSize) + j;
      recBuffer[byteNum] = SPIChannel(channel)->transfer(sendBuffer[byteNum]);
    }
    //Frame Complete, Set CS idel
    digitalWrite(csChan, (~csLL & 0x01) );
    DebugPrintln("In the right method");
  }
  return 0;
}

