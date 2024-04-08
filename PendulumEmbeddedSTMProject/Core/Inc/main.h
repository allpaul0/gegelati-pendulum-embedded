/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
	
  /* DWT (Data Watchpoint and Trace) registers, only exists on ARM Cortex with a DWT unit */
	#define Cortex_M4_DWT_CONTROL             (*((volatile uint32_t*)0xE0001000))
		/*!< DWT Control register */

	#define Cortex_M4_DWT_CYCCNTENA_BIT       (1UL<<0)
		/*!< CYCCNTENA bit in DWT_CONTROL register */

	#define Cortex_M4_DWT_CYCCNT              (*((volatile uint32_t*)0xE0001004))
		/*!< DWT Cycle Counter register */

	#define Cortex_M4_DEMCR                   (*((volatile uint32_t*)0xE000EDFC))
		/*!< DEMCR: Debug Exception and Monitor Control Register */

	#define Cortex_M4_TRCENA_BIT              (1UL<<24)
    /*!< Trace enable bit in DEMCR register */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

	#define Cortex_M4_InitCycleCounter() \
  	Cortex_M4_DEMCR |= Cortex_M4_TRCENA_BIT
	/*!< TRCENA: Enable trace and debug block DEMCR (Debug Exception and Monitor Control Register */
	
	#define Cortex_M4_ResetCycleCounter() \
	Cortex_M4_DWT_CYCCNT = 0
	/*!< Reset cycle counter */
	
	#define Cortex_M4_EnableCycleCounter() \
	Cortex_M4_DWT_CONTROL |= Cortex_M4_DWT_CYCCNTENA_BIT
	/*!< Enable cycle counter */
	
	#define Cortex_M4_DisableCycleCounter() \
	Cortex_M4_DWT_CONTROL &= ~Cortex_M4_DWT_CYCCNTENA_BIT
	/*!< Disable cycle counter */
	
	#define Cortex_M4_GetCycleCounter() \
	Cortex_M4_DWT_CYCCNT
	/*!< Read cycle counter register */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
