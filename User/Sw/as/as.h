#ifndef __AS_H__
#define __AS_H__

#include "rte.h"


#define AS_SLAVE_ADDR    0x36 << 1    //左移1位，要符合HAL库要求
#define AS_ANGLE_MAX     360          //角度最大值，范围18°~360°

typedef struct 
{
    uint8_t SlaveAddr;    //从机地址
    uint8_t RegAddr;      //寄存器地址

}AsInfo_t;  //角度传感器信息结构体

typedef enum
{
    AsAngleAddrIndex  = 0,     //角度寄存器地址
    AsRegAddrIndexMax,         //寄存器地址索引最大值

}AsRegAddrIndex_t;  //角度传感器寄存器地址枚举

void As_If_Init(void);
void As_If_Poll(void);

#endif /* __AS_H__ */