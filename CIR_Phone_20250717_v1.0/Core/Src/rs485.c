#include "rs485.h"
#include "usart.h"
#include "crc.h"

//通信协议由MODBUS基础上修改

MODBUS modbus;//结构体变量

uint8_t modbus_slave_addr = 0x40;              //从机地址
uint8_t modbus_Tx_buff[32];                //发送缓冲区

HOLDREG Reg[]= {{0x0000, 0x00, 0},                    
                {0x0001, 0x00, 0},                    
                {0x0002, 0x00, 0},                    
                {0x0003, 0x00, 0},                    
                {0x0004, 0x00, 0},                    
                {0x0005, 0x00, 0},                    
                {0x0006, 0x00, 0},                    
                {0x0007, 0x00, 0},                    
                {0x0008, 0x00, 0},
                {0x0009, 0x00, 0},
                {0x000A, 0x00, 0},
                {0x000B, 0x00, 0}
};



void modbus_send_data(uint8_t *buff, uint8_t len)//从机发送
{        
    RS485DIR_TX;
    HAL_Delay(1);
    /* 进入发送模式 */
    HAL_UART_Transmit_DMA(&huart1, (uint8_t *)buff, len);//发送数据
    HAL_Delay(1);
    RS485DIR_RX;
}

/* modbus服务函数 */
void modbus_service(void)
{
    uint16_t data_CRC_value;                //从机收到的CRC校验码
    uint16_t CRC_check_result;              //从机根据收到的数据计算出来的CRC校验码
    uint8_t frame_end;
    uint8_t frame_index;
    
    if(modbus.reflag == 0)
    {
        return;
    }
    
    if(modbus.reflag == 1)             //串口接收完成的标志
    {
        CRC_check_result = CRC16_XMODEM_T(&modbus.rcbuf[0], modbus.recount-3);
        // 读取数据帧的CRC
        data_CRC_value = ((modbus.rcbuf[modbus.recount-3]<<8))|
                         ((uint16_t)modbus.rcbuf[modbus.recount-2]);
        
        // 获取帧尾
        frame_index = modbus.rcbuf[2] + 5;

        frame_end = modbus.rcbuf[frame_index];
        
        // 校验 CRC 和帧尾是否正确
        if( CRC_check_result == data_CRC_value && frame_end == 0xEE )
        {
            if(modbus.rcbuf[1] == modbus_slave_addr)
            {
                modbus_16_function();//写多个寄存器
            }
        }
    }
        modbus.recount = 0; //接收计数清零
        modbus.reflag = 0;  //开始下一次接收
        
}

//从机功能码16
void modbus_16_function(void)
{
    uint16_t i;
    uint16_t register_start;        //修改寄存器的起始地址
    uint16_t register_num;          //修改寄存器的数量
    uint16_t CRC_check_result;      //CRC校验的结果
    uint8_t len;
    
    modbus_Tx_buff[0]=modbus.rcbuf[0];    //帧头
    modbus_Tx_buff[1]=modbus.rcbuf[1];    //从机地址
    modbus_Tx_buff[2]=modbus.rcbuf[2];    //数据长度
    
    
    //CRC校验获得 高位在左低位在右
    CRC_check_result = CRC16_XMODEM_T(modbus_Tx_buff, 3);
    modbus_Tx_buff[3]=(CRC_check_result>>8)&0xFF;
    modbus_Tx_buff[4]=(CRC_check_result)&0xFF;
    
    //帧尾
    len = modbus.rcbuf[2]+5;
    modbus_Tx_buff[5]=modbus.rcbuf[len];
    
    //起始地址
    register_start = 0;
    
    //寄存器数量
    register_num = modbus.rcbuf[2];    
    
    //将接收的数据保存到Reg.HoldRegData
    for(i = 0; i < register_num; i++)
    {
        Reg[register_start+i].HoldRegData = modbus.rcbuf[3+i];
    }
    //回应给主机
    modbus_send_data(modbus_Tx_buff,6);
}   



