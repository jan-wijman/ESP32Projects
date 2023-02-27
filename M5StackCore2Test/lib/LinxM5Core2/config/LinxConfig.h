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

#define DEBUG_ENABLED -1 // The number is the channel, -1 is no debugging
#define NUM_I2C_CHANS 2
#define NUM_SPI_CHANS 1
#define NUM_UART_CHANS 3 //was 4, het virtuel kanaal via BT, niet gebruikt
#define DEVICE_FAMILY 2 //was 7
#define LINX_DEVICE_FAMILY 2 //was 7

#define LINXWIFI

#define ARDUINO_VERSION 105


#endif //LINXCONFIG
