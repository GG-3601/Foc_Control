#ifndef __RTE_H__
#define __RTE_H__

#include "stm32f1xx_hal.h"
#include "freemaster.h"
#include "stdint.h"
#include "as.h"
#include "gpio.h"
#include "i2c.h"
#include "tms.h"
#include "usart.h"

typedef enum
{
    RteTargetAngleIdx = 0,     //目标角度
    RteActualAngleIdx ,        //实际角度
    RteIdxMax,          //索引最大值
}RteDataIdx_t;


void Rte_If_WriteData(RteDataIdx_t Idx, uint32_t* pData);
uint32_t Rte_If_ReadData(RteDataIdx_t Idx);

#endif /* __RTE_H__ */