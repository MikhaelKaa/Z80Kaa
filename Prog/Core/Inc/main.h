/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern uint8_t control_cmd;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Z80_RESET_Pin LL_GPIO_PIN_13
#define Z80_RESET_GPIO_Port GPIOC
#define D0_Pin LL_GPIO_PIN_0
#define D0_GPIO_Port GPIOA
#define D1_Pin LL_GPIO_PIN_1
#define D1_GPIO_Port GPIOA
#define D2_Pin LL_GPIO_PIN_2
#define D2_GPIO_Port GPIOA
#define D3_Pin LL_GPIO_PIN_3
#define D3_GPIO_Port GPIOA
#define D4_Pin LL_GPIO_PIN_4
#define D4_GPIO_Port GPIOA
#define D5_Pin LL_GPIO_PIN_5
#define D5_GPIO_Port GPIOA
#define D6_Pin LL_GPIO_PIN_6
#define D6_GPIO_Port GPIOA
#define D7_Pin LL_GPIO_PIN_7
#define D7_GPIO_Port GPIOA
#define A0_Pin LL_GPIO_PIN_0
#define A0_GPIO_Port GPIOB
#define A1_Pin LL_GPIO_PIN_1
#define A1_GPIO_Port GPIOB
#define A2_Pin LL_GPIO_PIN_2
#define A2_GPIO_Port GPIOB
#define A10_Pin LL_GPIO_PIN_10
#define A10_GPIO_Port GPIOB
#define A11_Pin LL_GPIO_PIN_11
#define A11_GPIO_Port GPIOB
#define A12_Pin LL_GPIO_PIN_12
#define A12_GPIO_Port GPIOB
#define A13_Pin LL_GPIO_PIN_13
#define A13_GPIO_Port GPIOB
#define A14_Pin LL_GPIO_PIN_14
#define A14_GPIO_Port GPIOB
#define A15_Pin LL_GPIO_PIN_15
#define A15_GPIO_Port GPIOB
#define BUSRQ_Pin LL_GPIO_PIN_8
#define BUSRQ_GPIO_Port GPIOA
#define WR_Pin LL_GPIO_PIN_9
#define WR_GPIO_Port GPIOA
#define RD_Pin LL_GPIO_PIN_10
#define RD_GPIO_Port GPIOA
#define MREQ_Pin LL_GPIO_PIN_15
#define MREQ_GPIO_Port GPIOA
#define A3_Pin LL_GPIO_PIN_3
#define A3_GPIO_Port GPIOB
#define A4_Pin LL_GPIO_PIN_4
#define A4_GPIO_Port GPIOB
#define A5_Pin LL_GPIO_PIN_5
#define A5_GPIO_Port GPIOB
#define A6_Pin LL_GPIO_PIN_6
#define A6_GPIO_Port GPIOB
#define A7_Pin LL_GPIO_PIN_7
#define A7_GPIO_Port GPIOB
#define A8_Pin LL_GPIO_PIN_8
#define A8_GPIO_Port GPIOB
#define A9_Pin LL_GPIO_PIN_9
#define A9_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
