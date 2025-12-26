#ifndef _MODBUS_H
#define _MODBUS_H
#include "main.h"

#define MODBUS_RX_MAX_LEN 32

typedef struct
{
    uint16_t HoldRegAddr;       //地址    
    uint16_t HoldRegData;       //数据
    uint16_t safeLevel;         //读写权限
}HOLDREG;

typedef struct 
{
    //作为从机时使用
    uint8_t  myadd;                            //本设备从机地址
    uint8_t  rcbuf[MODBUS_RX_MAX_LEN];         //modbus接受缓冲区
    uint8_t  recount;                          //modbus端口接收到的数据个数
    uint8_t  reflag;                           //modbus一帧数据接受完成标志位
    uint8_t  sendbuf[MODBUS_RX_MAX_LEN];       //modbus接发送缓冲区
}MODBUS;

extern MODBUS modbus;
extern HOLDREG Reg[];

void modbus_service(void);
void modbus_03_function(void);
void modbus_06_function(void);
void modbus_16_function(void);
void modbus_send_data(uint8_t *buff, uint8_t len);

#endif
