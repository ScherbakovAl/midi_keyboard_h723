/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SH_LD_Pin GPIO_PIN_0
#define SH_LD_GPIO_Port GPIOA
#define CLK_Pin GPIO_PIN_1
#define CLK_GPIO_Port GPIOA
#define AND_Pin GPIO_PIN_2
#define AND_GPIO_Port GPIOA
#define AND_OFF_Pin GPIO_PIN_3
#define AND_OFF_GPIO_Port GPIOA
#define POWER_1_Pin GPIO_PIN_4
#define POWER_1_GPIO_Port GPIOA
#define POWER_2_Pin GPIO_PIN_5
#define POWER_2_GPIO_Port GPIOA
#define Encoder_ch1_Pin GPIO_PIN_6
#define Encoder_ch1_GPIO_Port GPIOA
#define Encoder_ch2_Pin GPIO_PIN_7
#define Encoder_ch2_GPIO_Port GPIOA
#define Encoder_ch0_Pin GPIO_PIN_4
#define Encoder_ch0_GPIO_Port GPIOC
#define LCD_CS_Pin GPIO_PIN_11
#define LCD_CS_GPIO_Port GPIOE
#define LCD_WR_RS_Pin GPIO_PIN_13
#define LCD_WR_RS_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
