/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body, used for energy consumption measurements.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <cstdbool>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <limits> 

#include "PendulumExecutionEnvironment.h"
#include "TimingBench.h"
#include "PendulumINA219Bench.h"
#include "PendulumINA219Monitor.h"
#include "ina219.h"
#include "TimeUnit.h"
#include "TPGPrograms.h"

#if GRAPH_LEVEL_ANALYSIS == 1
#include "seeds_nbActionsToTerminal.h"
#endif

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define NB_SAMPLES 1 // 3 

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// === Pendulum global access and parameters === */

PendulumExecutionEnvironment* pendulumEE_ptr;
#if INSTRUCTION_LEVEL_ANALYSIS == 1
    uint32_t nbActions = 1;  // Number of actions per inference
#elif INSTRUCTION_LEVEL_ANALYSIS == 0 && GRAPH_LEVEL_ANALYSIS == 1 &&  TYPE_INT == 1
    uint32_t nbActions = 15000;//20000;  // Set nbActions to 500000 if TYPE_INT is 1
#elif INSTRUCTION_LEVEL_ANALYSIS == 0 && GRAPH_LEVEL_ANALYSIS == 1 &&  TYPE_INT == 0
    uint32_t nbActions = 3000;// 5000;   // Default to 50000 if TYPE_INT is 0
#endif
double initAngle = 0.0;
double initVelocity = 0.0;

// === Measurements and log ===
INA219_t ina219t;
const char logStartBench[] = "##### Log Start Bench #####";
const char logEndBench[] = "##### Log End Bench #####";
const char logStartEnergy[] = "##### Log Start Energy #####";
const char logEndEnergy[] = "##### Log End Energy #####";
const char logStartTiming[] = "##### Log Start Timing #####";
const char logEndTiming[] = "##### Log End Timing #####";



// === TPG ===

uint32_t seed = 0;  // Seed use to reset the PendulumEnvironment
extern "C" {
  #if TYPE_INT == 1
	extern int* in1;
  #else
	extern double* in1;
  #endif
}


//#define DO_EXPAND(VAL)  VAL ## 1
//#define EXPAND(VAL)     DO_EXPAND(VAL)

//#if !defined(CPPFLAGS) || (EXPAND(CPPFLAGS) == 1)
//    #error "Only here if CPPFLAGS is not defined OR CPPFLAGS is the empty string."
//#endif

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* Benchmark function prototype */
void benchWrapper(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @return int
  */
int main(void)
{
	/* USER CODE BEGIN 1 */
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_TIM5_Init();
	MX_TIM7_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */

	/* == Pendulum Execution Environment === */
	std::vector<double> availableAction = {0.05, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0};
	PendulumExecutionEnvironment pendulumEE(availableAction);
	in1 = pendulumEE.modifiedState;
	pendulumEE_ptr = &pendulumEE;


	// Reset pendulum environment and store the initial conditions
#if GRAPH_LEVEL_ANALYSIS == 1
  uint16_t nbSeeds = NB_SEED; //100
	pendulumEE.reset(seeds[0]);
#else
	pendulumEE.reset(seed);
#endif
	initAngle = pendulumEE.getAngle();
	initVelocity = pendulumEE.getVelocity();

	/* === INA219 setup === */
	if(INA219_Init(&ina219t, &hi2c1, INA219_DEFAULT_ADDRESS, 3.2768) == 0){
		std::cout << "Can't access the INA219 sensor, end of program" << std::endl;
		while(1){}	// Waiting for reset
	}
	INA219_setConfig(&ina219t, INA219_CONFIG_BADCRES_12BIT | INA219_CONFIG_BVOLTAGERANGE_32V
								| INA219_CONFIG_GAIN_1_40MV | INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS
								| INA219_CONFIG_SADCRES_12BIT);	// 0x219f

	/* === Benchmark === */

	// Timers are configure as follows :
	// - TIM5, used for timing benches, count each microseconds.
	// - TIM7, used for energy monitoring count each 0.1 milliseconds and raise an interrupt every 3 milliseconds.
	PendulumINA219Bench energybench(benchWrapper, &ina219t, &pendulumEE, &htim7, TimeUnit::Milliseconds, 3.f); // current and power measure bench (provides cycle count to make sure the bench is fair)
	TimingBench executionTimingBench(benchWrapper, &htim5, TimeUnit::Microseconds); // timing bench 

	Cortex_M4_InitCycleCounter(); /* enable DWT hardware */
	Cortex_M4_EnableCycleCounter(); /* start counting */

	char buffStart;
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
	while (1)
	{
    //synchronization with PC
	  do {
		  read(STDIN_FILENO, &buffStart, sizeof(char)); // receive (ACK) signal
		  HAL_Delay(1000);  // wait for 1 second
		}
		while (buffStart != '\n'); // (ACK) signal is a newline character

	  int coeff = COEFF_DYNAMIC_OPPENING;

#if TYPE_INT == 1
	  std::cout << "TYPE_INT=1, COEFF_DYNAMIC_OPPENING:" << coeff << std::endl;
#else
    std::cout << "TYPE_DOUBLE, COEFF_DYNAMIC_OPPENING:" << coeff << std::endl;
#endif

    int ila = INSTRUCTION_LEVEL_ANALYSIS;
    int gla = GRAPH_LEVEL_ANALYSIS;
    int pt = PENDULUM_TRACE;
    std::cout << "INSTRUCTION_LEVEL_ANALYSIS: " << ila
              << "GRAPH_LEVEL_ANALYSIS: " << gla
              << "PENDULUM_TRACE: " << pt << std::endl;

#if GRAPH_LEVEL_ANALYSIS == 1
    std::cout << "NB_SEED: " << NB_SEED << std::endl;
    for(int idSeed=0; idSeed<nbSeeds; idSeed++){
#endif
      for(int idSample=0; idSample<NB_SAMPLES; idSample++){
        
        std::cout << logStartBench << std::endl;
        Cortex_M4_ResetCycleCounter();  /* Reset cycle counter */
        
        std::cout << "NB_SAMPLES : " << NB_SAMPLES << std::endl;
#if INSTRUCTION_LEVEL_ANALYSIS == 1
        std::cout << "NB_ITERATIONS_FUNC : " << NB_ITERATIONS_FUNC << std::endl;
#endif
#if GRAPH_LEVEL_ANALYSIS == 1
        std::cout << "SEED : " << seeds[idSeed] << std::endl;
        std::cout << "ITERATION_NUMBER : " << idSeed << std::endl;
        std::cout << "ID_SAMPLE : " << idSample << std::endl;
        std::cout << "NB_ACTIONS : " << nbActions << std::endl;
        pendulumEE_ptr->reset(angles[idSeed], velocities[idSeed]);
#endif

        /* Energy consumption measurements */
        std::cout << logStartEnergy << std::endl;
        energybench.startBench();
        energybench.printResult();
        std::cout << logEndEnergy << std::endl;

        /* Execution time measurement without energy measurement interruptions */
        std::cout << logStartTiming << std::endl;
        executionTimingBench.startBench();
        executionTimingBench.printResult();
        std::cout << logEndTiming << std::endl;

        std::cout << logEndBench << std::endl;
      }
#if GRAPH_LEVEL_ANALYSIS == 1
    }
#endif
    std::cout << "END" << std::endl;

    Cortex_M4_DisableCycleCounter(); /* disable counting if not used any more */

    while(1) {}		// Waiting for reset

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* Function for benchmarks */
void benchWrapper(void){
  pendulumEE_ptr->startInference((int)nbActions);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
