#ifndef __CRC_H__
#define __CRC_H__

unsigned short CRC16_XMODEM_T(unsigned char *ptr, unsigned int len);
unsigned short modbus_CRC16(unsigned char *puchMsg, unsigned char usDataLen);

#endif
