/****************************************************************************************
**  LINX Configuration data for the ESP32
**
**  For more information see:           www.labviewmakerhub.com/linx
**  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
**
**  Written By Ken Sharp
**
** BSD2 License.
****************************************************************************************/

#ifndef LINXCONFIG

#define LINXCONFIG

#define DEBUG_ENABLED 0
//#define NUM_I2C_CHANS 2
//#define NUM_SPI_CHANS 3
#define NUM_UART_CHANS 4
#define DEVICE_FAMILY 0xAE //7

#define LINXWIFI

#define ARDUINO_VERSION 105

// Define ALTERNATE_PINS to use non-standard GPIO pins for SPI bus

#ifdef ALTERNATE_PINS
  #define VSPI_MISO   2
  #define VSPI_MOSI   4
  #define VSPI_SCLK   0
  #define VSPI_SS     33

  #define HSPI_MISO   26
  #define HSPI_MOSI   27
  #define HSPI_SCLK   25
  #define HSPI_SS     32
#else
  #define VSPI_MISO   19 //MISO
  #define VSPI_MOSI   23 //MOSI
  #define VSPI_SCLK   18 //SCK
  #define VSPI_SS     5 //SS

  #define HSPI_MISO   12
  #define HSPI_MOSI   13
  #define HSPI_SCLK   14
  #define HSPI_SS     15
#endif

//#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
//#define VSPI FSPI
//#endif

#endif //LINXCONFIG
