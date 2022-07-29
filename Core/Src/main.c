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
#include "LCD_Routines.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile float measured_amb_temp = 0.0f;
volatile float measured_hotplate_temp = 0.0f;
volatile int STATE = 0;
volatile float user_temp = 30.0f;
volatile float user_preheat_temp = 30.0f;
volatile float user_preheat_time = 5.0f;
volatile float user_reflow_time = 5.0f;
volatile int set_user_temp_flag = 0;
PIController fan = 	{ .Kp = FAN_KP, .Ki = FAN_KI, .lim_min_int = FAN_LIM_MIN_INT,
				  .lim_max_int = FAN_LIM_MAX_INT, .lim_min = FAN_LIM_MAX,
				  .lim_max = FAN_LIM_MAX, .T = PERIOD
					};
PIController hotplate = { .Kp = FAN_KP, .Ki = FAN_KI, .lim_min_int = FAN_LIM_MIN_INT,
						  .lim_max_int = FAN_LIM_MAX_INT, .lim_min = FAN_LIM_MAX,
						  .lim_max = FAN_LIM_MAX, .T = PERIOD
						};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* Initialize peripherals, fan, and hotplate, control systems in off state, LCD display IDLE */
void System_Initialization()
{

	/* Disable all peripherals */
	HAL_GPIO_WritePin(SENS_DIS_GPIO_Port, SENS_DIS_Pin, GPIO_PIN_SET);	// Disable sensors
	HAL_GPIO_WritePin(EN_12V_GPIO_Port, EN_12V_Pin, GPIO_PIN_SET);		// Disable hotplate voltage
	PWM_Update(fan_pwm, TIM_CHANNEL_1, 1);								// Disable fan (100% DC)
	PWM_Update(hotplate_pwm, TIM_CHANNEL_1, 1);							// Disable hotplate (100% DC)

	/* Initialize control structures */
	Controller_Init(&fan);
	Controller_Init(&hotplate);

	/* Initialize LCD */
	LCD_init();
	LCD_Refresh(STATE);

};

/* Find oscillation for ZN calculation of controller gains */
void ZN_Tuning()
{

	  // Enable sensors
	  HAL_GPIO_WritePin(SENS_DIS_GPIO_Port, SENS_DIS_Pin, GPIO_PIN_RESET);

	  // Start hotplate at 50% Duty Cycle
	HAL_TIM_PWM_Start(hotplate_pwm, TIM_CHANNEL_1);
	PWM_Update(hotplate_pwm, TIM_CHANNEL_1, .5);

	// Set integral gain to 0
	hotplate.Ki = 0;

	while (1) {

		// Use the user temp to configure KP gain
		hotplate.Kp = user_temp;

		// Observe temperature response
		update_temps();
		LCD_updt_temps(&measured_hotplate_temp, &measured_amb_temp);
		LCD_Refresh(2);
		HAL_Delay(100);
	}

	/* Note on final gain calculations: */
	/* Gain at which system critically stable: Ku
	 * Period of oscillation at critical stability: Pu
	 * Kp = Ku / 2.2
	 * Ki = Kp * T / ( Pu / 1.2 )
	 *
	 * */


};

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* Update current system temperatures */
void update_temps()
{
	  measured_amb_temp = read_ambient_temp();
	  measured_hotplate_temp = read_plate_temp();
};
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
  MX_TIM1_Init();
  MX_TIM11_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  /** Initialize System **/
  System_Initialization();

  /** Take measurements for calculation of PI gain constants **/
//  ZN_Tuning();

  // Initialize local variables
  int heating_stage = 0;
  int graph_refresh = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  /** SYSTEM STATE MACHINE **/
	  switch (STATE)
	  {

		  // Idle state
		  case 0:

			  // Display Idle screen
			  LCD_Refresh(STATE);

			  // Reset local variables
			  heating_stage = 0;
			  graph_refresh = 0;

				/* Disable all peripherals */
				HAL_GPIO_WritePin(SENS_DIS_GPIO_Port, SENS_DIS_Pin, GPIO_PIN_SET);	// Disable sensors
				HAL_GPIO_WritePin(EN_12V_GPIO_Port, EN_12V_Pin, GPIO_PIN_SET);		// Disable hotplate voltage
				PWM_Update(fan_pwm, TIM_CHANNEL_1, 1);								// Disable fan (100% DC)
				PWM_Update(hotplate_pwm, TIM_CHANNEL_1, 1);							// Disable hotplate (100% DC)

			  break;

		  // Display Setup screen
		  case 1:

			  // Enable Plate Power
			  HAL_GPIO_WritePin(EN_12V_GPIO_Port, EN_12V_Pin, GPIO_PIN_RESET);

			  // Enable sensors
			  HAL_GPIO_WritePin(SENS_DIS_GPIO_Port, SENS_DIS_Pin, GPIO_PIN_RESET);

			  // Enable fan
			  PWM_Update(fan_pwm, TIM_CHANNEL_1, .5);

			  // Enable LCD
			  HAL_GPIO_WritePin(DISP_DIS_GPIO_Port, DISP_DIS_Pin, GPIO_PIN_RESET);

			  // Update user inputs and display
			  LCD_usr_inputs(&user_preheat_temp, &user_preheat_time, &user_temp, &user_reflow_time);
			  LCD_Refresh(STATE);
			  update_temps();

			  break;

		  // Display heating screen
		  case 2:

				  // Update LCD less frequently to remove screen refresh overhead
				  if (graph_refresh == 0) {	// Scuffed timerless version of slowing refresh rate

					  LCD_updt_temps(&measured_hotplate_temp, &measured_amb_temp);
					  LCD_Refresh(STATE);

				  }
				  graph_refresh = (graph_refresh + 1) % 100;

				  // Update temperature measurements for control fx
				  update_temps();

						  switch (heating_stage)
						  {

						  // First stage, max hotplate PWM to reach preheat temp
						  case 0:

							  // If hotplate is below desired temp, max out
							  if (measured_hotplate_temp < user_temp) {

								  PWM_Update(hotplate_pwm, TIM_CHANNEL_1, 0.0);	// Max plate by turning FET off

							  } else { // If hotplate has reached desired temp, move to next stage

								  heating_stage++;

							  }

							  break;

						  // Second stage, maintain hotplate at preheat temp for xxx time
						  case 1:

							  // Check if timer enabled, start timer
							  if (HAL_TIM_Base_GetState(control_timer) != HAL_TIM_STATE_BUSY) {

								  start_preheat();


							  }	else if ( preheat_status() ){	// If preheat time has been completed

								  HAL_TIM_Base_Stop_IT(control_timer);
								  heating_stage++;

							  }

							  break;

						  // Third stage, max hotplate PWM to reach reflow temp
						  case 2:

							  // If hotplate is below desired temp, max out
							  if (measured_hotplate_temp < user_temp) {

								  PWM_Update(hotplate_pwm, TIM_CHANNEL_1, 0.0);	// Max plate by turning FET off

							  } else { // If hotplate has reached desired temp, move to next stage

								  heating_stage++;

							  }

							  break;

						  // Fourth stage, maintain hotplate at reflow temp for xxx time
						  case 3:

							  // Check if timer enabled, start timer
							  if (HAL_TIM_Base_GetState(control_timer) != HAL_TIM_STATE_BUSY) {

								  start_reflow();


							  }	else if ( reflow_status() ){	// If reflow time has been completed

								  HAL_TIM_Base_Stop_IT(control_timer);

								  // Reset heating_stage
								  heating_stage = 0;

								  // Send system state back to initialization
								  STATE = 0;

							  }

							  break;

						  default :

							  break;

						  }

		  default :

			  break;

		  }

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
