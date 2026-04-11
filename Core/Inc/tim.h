/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim1;

/* USER CODE BEGIN Private defines */

typedef enum
{
    Tim1 = 0,
    Tim2,
    Tim3,
    Tim4,
}TimTimer_t;

typedef enum
{
    TimChannel1  = 0x00000000U,
    TimChannel2  = 0x00000004U,
    TimChannel3  = 0x00000008U,
    TimChannel4  = 0x0000000CU,
    TimChanleAll = 0x0000003CU
}TimChannel_t;


/* USER CODE END Private defines */

void MX_TIM1_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN Prototypes */
void Tim_If_PwmOutputEn(void);
void Tim_If_SetPwmDuty(TimTimer_t Timer, TimChannel_t Channel, uint16_t Duty);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

