/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"
#include "string"
#include <midi_keyboard.h>

extern "C" {
#include "lcd.h"
}

void SystemClock_Config(void);

cuint extpr0 = 1;
cuint extpr1 = 2;
cuint extpr2 = 4;
cuint extpr3 = 8;
cuint extpr4 = 16;
cuint extpr5 = 32;
cuint extpr6 = 64;
cuint extpr7 = 128;
cuint extpr8 = 256;
cuint extpr9 = 512;
cuint extpr10 = 1024;

cuint interrupt0 = 0;
cuint interrupt1 = 1;
cuint interrupt2 = 2;
cuint interrupt3 = 3;
cuint interrupt4 = 4;
cuint interrupt5 = 5;
cuint interrupt6 = 6;
cuint interrupt7 = 7;
cuint interrupt8 = 8;
cuint interrupt9 = 9;
cuint interrupt10 = 10;
Keys keys;

int main(void) {
	SCB_EnableICache();
	SCB_EnableDCache();
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_SPI4_Init();
	MX_TIM1_Init();
	MX_TIM3_Init();
	MX_TIM2_Init();//4294967295
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	LCD_Start();

//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv управление питанием
	if (!__HAL_PWR_GET_FLAG(PWR_FLAG_SB)) {
//		LCD_stby?
		HAL_Delay(500);
		HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN4); //pin4 == кнопка К1 на плате
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN4);
		HAL_PWR_EnterSTANDBYMode();
	} else {
		HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN4);
//		LCD_start?
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ управление питанием

	MX_USB_DEVICE_Init();
	HAL_Delay(300);
	keys.wheel();

	while (1) {
	}
}

void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

	while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {
	}

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48
			| RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 2;
	RCC_OscInitStruct.PLL.PLLN = 44;
	RCC_OscInitStruct.PLL.PLLP = 1;
	RCC_OscInitStruct.PLL.PLLQ = 5;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1
			| RCC_CLOCKTYPE_D1PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
		Error_Handler();
	}
}

//===============================================================================================================================================
// extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C"
extern "C" {
void EXTI0_IRQHandler(void) {
	EXTI->PR1 = extpr0;
	keys.interrupt(interrupt0);
}
void EXTI1_IRQHandler(void) {
	EXTI->PR1 = extpr1;
	keys.interrupt(interrupt1);
}
void EXTI2_IRQHandler(void) {
	EXTI->PR1 = extpr2;
	keys.interrupt(interrupt2);
}
void EXTI3_IRQHandler(void) {
	EXTI->PR1 = extpr3;
	keys.interrupt(interrupt3);
}
void EXTI4_IRQHandler(void) {
	EXTI->PR1 = extpr4;
	keys.interrupt(interrupt4);
}
void EXTI9_5_IRQHandler(void) {
	if ((EXTI->PR1 & EXTI_PR1_PR5) == EXTI_PR1_PR5) {
		EXTI->PR1 = extpr5;
		keys.interrupt(interrupt5);
	}
	if ((EXTI->PR1 & EXTI_PR1_PR6) == EXTI_PR1_PR6) {
		EXTI->PR1 = extpr6;
		keys.interrupt(interrupt6);
	}
	if ((EXTI->PR1 & EXTI_PR1_PR7) == EXTI_PR1_PR7) {
		EXTI->PR1 = extpr7;
		keys.interrupt(interrupt7);
	}
	if ((EXTI->PR1 & EXTI_PR1_PR8) == EXTI_PR1_PR8) {
		EXTI->PR1 = extpr8;
		keys.interrupt(interrupt8);
	}
	if ((EXTI->PR1 & EXTI_PR1_PR9) == EXTI_PR1_PR9) {
		EXTI->PR1 = extpr9;
		keys.interrupt(interrupt9);
	}
}

void EXTI15_10_IRQHandler(void) {
	if ((EXTI->PR1 & EXTI_PR1_PR10) == EXTI_PR1_PR10) {
		EXTI->PR1 = extpr10;
		keys.interrupt(interrupt10);
	}
}
} // extern "C"

// extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C" extern "C"
//===============================================================================================================================================

void Error_Handler(void) {
	__disable_irq();
	while (1) {
	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
