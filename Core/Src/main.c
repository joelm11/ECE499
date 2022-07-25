/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "lptim.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LCD_Test.h"
#include "image.h"
#include "LCD_Test.h"
#include "LCD_1in8.h"
#include "DEV_Config.h"
#include "SensorInterfacing.h"
#include "PWM_Config.h"
#include "Control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
volatile int STATE = 0;
#define PID_KP  1.0f
#define PID_KI  0.25f
#define PID_LIM_MIN 0.0f
#define PID_LIM_MAX  1.0f
#define PID_LIM_MIN_INT -5.0f
#define PID_LIM_MAX_INT  5.0f
#define PERIOD 0.45f
#define SIM_TIME 9.0f
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//volatile extern int STATE;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
float TestSystem_Update(float inp) {

    static float output = 0.0f;
    static const float alpha = 0.02f;

    output = (PERIOD * inp + output) / (1.0f + alpha * PERIOD);

    return output;
};
void lcd_testing()
{

	// Begin LCD Init
	DEV_Module_Init();
	LCD_1IN8_Init(SCAN_DIR_DFT);
	LCD_1IN8_Clear(BLACK);
	Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);
	Paint_SetClearFuntion(LCD_1IN8_Clear);
	Paint_SetDisplayFuntion(LCD_1IN8_DrawPaint);
	Paint_Clear(WHITE);
	// End LCD Init

	// Initialization routine:
	Paint_DrawImage(gImage_70X70, 1, 30, 100, 100);
//	Paint_DrawImage(gImage_1,80,35,60,60);

};

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
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
  MX_SPI1_Init();
  MX_TIM9_Init();
  MX_LPTIM1_Init();
  MX_TIM1_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */

  // Testing LCD
  lcd_testing();

//  // Testing PI Control
//  HAL_TIM_Base_Start_IT(&htim5);
//  PIController sys;
//  sys.Kp = PID_KP;
//  sys.Ki = PID_KI;
//  sys.lim_min_int = PID_LIM_MIN_INT;
//  sys.lim_max_int = PID_LIM_MIN_INT;
//  sys.lim_min = PID_LIM_MIN;
//  sys.lim_max = PID_LIM_MAX;
//  sys.T = PERIOD;
//
//  Controller_Init(&sys);
//  float setpoint = 0.5f;
//  for (float t = 0.0f; t <= SIM_TIME; t += PERIOD) {
//
//	  float measurement = TestSystem_Update(sys.out);
//	  Controller_Update(&sys, setpoint, measurement);
//	  HAL_Delay(1);
//  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  // Switch for LCD display modes which will be toggled through via
	  // the switch on the rotary encoder
//	  STATE %= 3;
//	  switch(STATE){
//
//		  // Initialization / Idle / Stopped screen
//		  case 0:
//			  HAL_GPIO_WritePin(GPIOC, LED_R_Pin, GPIO_PIN_SET);
//			  HAL_GPIO_WritePin(GPIOC, LED_G_Pin, GPIO_PIN_RESET);
//			  HAL_GPIO_WritePin(GPIOC, LED_B_Pin, GPIO_PIN_RESET);
//			  break;
//		  // Start heating routines
//		  case 1:
//			  HAL_GPIO_WritePin(GPIOC, LED_G_Pin, GPIO_PIN_SET);
//			  HAL_GPIO_WritePin(GPIOC, LED_R_Pin, GPIO_PIN_RESET);
//			  HAL_GPIO_WritePin(GPIOC, LED_B_Pin, GPIO_PIN_RESET);
//			  break;
//		  // Temperature reached (buzzer as well), continue heating routines
//		  case 2:
//			  HAL_GPIO_WritePin(GPIOC, LED_B_Pin, GPIO_PIN_SET);
//			  HAL_GPIO_WritePin(GPIOC, LED_R_Pin, GPIO_PIN_RESET);
//			  HAL_GPIO_WritePin(GPIOC, LED_G_Pin, GPIO_PIN_RESET);
//			  break;
//
//		  default:
//			  break;
//	  }



//	  HAL_Delay(20);
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
