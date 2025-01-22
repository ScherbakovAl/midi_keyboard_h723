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
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOE
#define PWR_WKUP_Pin GPIO_PIN_13
#define PWR_WKUP_GPIO_Port GPIOC
#define SH_LD_Pin GPIO_PIN_0
#define SH_LD_GPIO_Port GPIOA
#define CLK_Pin GPIO_PIN_1
#define CLK_GPIO_Port GPIOA
#define AND_Pin GPIO_PIN_2
#define AND_GPIO_Port GPIOA
#define AND_OFF_Pin GPIO_PIN_3
#define AND_OFF_GPIO_Port GPIOA
#define POWER_SENSORS_1_Pin GPIO_PIN_4
#define POWER_SENSORS_1_GPIO_Port GPIOA
#define POWER_SENSORS_2_Pin GPIO_PIN_5
#define POWER_SENSORS_2_GPIO_Port GPIOA
#define Encoder_ch1_Pin GPIO_PIN_6
#define Encoder_ch1_GPIO_Port GPIOA
#define Encoder_ch2_Pin GPIO_PIN_7
#define Encoder_ch2_GPIO_Port GPIOA
#define Encoder_ch0_Pin GPIO_PIN_4
#define Encoder_ch0_GPIO_Port GPIOC
#define test_out0_Pin GPIO_PIN_1
#define test_out0_GPIO_Port GPIOB
#define test_out1_Pin GPIO_PIN_7
#define test_out1_GPIO_Port GPIOE
#define test_out2_Pin GPIO_PIN_9
#define test_out2_GPIO_Port GPIOE
#define LCD_TIM_Pin GPIO_PIN_10
#define LCD_TIM_GPIO_Port GPIOE
#define LCD_CS_Pin GPIO_PIN_11
#define LCD_CS_GPIO_Port GPIOE
#define LCD_SCK_Pin GPIO_PIN_12
#define LCD_SCK_GPIO_Port GPIOE
#define LCD_WR_RS_Pin GPIO_PIN_13
#define LCD_WR_RS_GPIO_Port GPIOE
#define LCD_MOSI_Pin GPIO_PIN_14
#define LCD_MOSI_GPIO_Port GPIOE
#define MCP4351_SCK_Pin GPIO_PIN_13
#define MCP4351_SCK_GPIO_Port GPIOB
#define MCP4351_MOSI_Pin GPIO_PIN_15
#define MCP4351_MOSI_GPIO_Port GPIOB
#define in8_Pin GPIO_PIN_8
#define in8_GPIO_Port GPIOD
#define in8_EXTI_IRQn EXTI9_5_IRQn
#define in9_Pin GPIO_PIN_9
#define in9_GPIO_Port GPIOD
#define in9_EXTI_IRQn EXTI9_5_IRQn
#define in10_Pin GPIO_PIN_10
#define in10_GPIO_Port GPIOD
#define in10_EXTI_IRQn EXTI15_10_IRQn
#define DIPOT_0_Pin GPIO_PIN_7
#define DIPOT_0_GPIO_Port GPIOC
#define DIPOT_1_Pin GPIO_PIN_9
#define DIPOT_1_GPIO_Port GPIOC
#define USB_HS_DM_Pin GPIO_PIN_11
#define USB_HS_DM_GPIO_Port GPIOA
#define USB_HS_DP_Pin GPIO_PIN_12
#define USB_HS_DP_GPIO_Port GPIOA
#define DEBUG_DIO_Pin GPIO_PIN_13
#define DEBUG_DIO_GPIO_Port GPIOA
#define DEBUG_CLK_Pin GPIO_PIN_14
#define DEBUG_CLK_GPIO_Port GPIOA
#define in0_Pin GPIO_PIN_0
#define in0_GPIO_Port GPIOD
#define in0_EXTI_IRQn EXTI0_IRQn
#define in1_Pin GPIO_PIN_1
#define in1_GPIO_Port GPIOD
#define in1_EXTI_IRQn EXTI1_IRQn
#define in2_Pin GPIO_PIN_2
#define in2_GPIO_Port GPIOD
#define in2_EXTI_IRQn EXTI2_IRQn
#define in3_Pin GPIO_PIN_3
#define in3_GPIO_Port GPIOD
#define in3_EXTI_IRQn EXTI3_IRQn
#define in4_Pin GPIO_PIN_4
#define in4_GPIO_Port GPIOD
#define in4_EXTI_IRQn EXTI4_IRQn
#define in5_Pin GPIO_PIN_5
#define in5_GPIO_Port GPIOD
#define in5_EXTI_IRQn EXTI9_5_IRQn
#define in6_Pin GPIO_PIN_6
#define in6_GPIO_Port GPIOD
#define in6_EXTI_IRQn EXTI9_5_IRQn
#define in7_Pin GPIO_PIN_7
#define in7_GPIO_Port GPIOD
#define in7_EXTI_IRQn EXTI9_5_IRQn
#define multiplexer_A0_Pin GPIO_PIN_3
#define multiplexer_A0_GPIO_Port GPIOB
#define multiplexer_A1_Pin GPIO_PIN_5
#define multiplexer_A1_GPIO_Port GPIOB
#define multiplexer_A2_Pin GPIO_PIN_7
#define multiplexer_A2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
