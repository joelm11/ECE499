/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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
//#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Control.h"
#include "PWM_Config.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
volatile int tick_counter = 0;
volatile int heat_time = 0;
volatile int preheat_complete = 0;
volatile int reflow_complete = 0;
volatile int heat_complete = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void start_preheat()
{
	heat_complete = 0;
	heat_time = user_preheat_time;
	HAL_TIM_Base_Start_IT(control_timer);

}
void start_reflow()
{

	heat_complete = 0;
	heat_time = user_reflow_time;
	HAL_TIM_Base_Start_IT(control_timer);

}
int preheat_status()
{
	return heat_complete;
}
int reflow_status()
{
	return heat_complete;
}
int get_ticks()
{
	return tick_counter;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim9;
/* USER CODE BEGIN EV */
extern TIM_HandleTypeDef htim6;
extern PIController fan;
extern PIController hotplate;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 break interrupt and TIM9 global interrupt.
  */
void TIM1_BRK_TIM9_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_TIM9_IRQn 0 */

  /* USER CODE END TIM1_BRK_TIM9_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  HAL_TIM_IRQHandler(&htim9);
  /* USER CODE BEGIN TIM1_BRK_TIM9_IRQn 1 */

  /* USER CODE END TIM1_BRK_TIM9_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

	/* BEGIN INTERRUPT MASKING FOR ENCODER */

	// Check pushbutton
	if(!HAL_GPIO_ReadPin(GPIOB, ROT_SW_Pin)) {

		// If pushbutton pressed, start a timer to check for a hold
		HAL_TIM_Base_Start(&htim6);
		while(__HAL_TIM_GET_COUNTER(&htim6) < 5000);

		// If the button has been held for the length of the timer, change state
		if(!HAL_GPIO_ReadPin(GPIOB, ROT_SW_Pin)) {

			STATE = (STATE + 1) % 3;

		}	else {	// Otherwise, the button was tapped to set other parameter

				set_user_temp_flag = (set_user_temp_flag + 1) % 4;

		}

		// Reset the timer for the next iteration
		HAL_TIM_Base_Stop(&htim6);
		__HAL_TIM_SET_COUNTER(&htim6, 0);

	} else {	// If the pushbutton didn't trigger the interrupt, one of the rotary encoder twists must have

		// If CW, A goes LO first while B is HI
		if(!HAL_GPIO_ReadPin(GPIOB, DEB_A_Pin) && HAL_GPIO_ReadPin(GPIOB, DEB_B_Pin)) {

			// Update whichever variable is selected on the display
			switch (set_user_temp_flag) {

			case 0:
				user_preheat_temp++;
				break;
			case 1:
				user_preheat_time++;
				break;
			case 2:
				user_temp++;
				break;
			case 3:
				user_reflow_time++;
				break;
			default:
				break;
			}


		} else { 	// Otherwise it is a CCW rotation

			// Update whichever variable is selected on the display
			switch (set_user_temp_flag) {

			case 0:
				user_preheat_temp--;
				break;
			case 1:
				user_preheat_time--;
				break;
			case 2:
				user_temp--;
				break;
			case 3:
				user_reflow_time--;
				break;
			default:
				break;
			}

		}

	}

	/* END INTERRUPT MASKING FOR ENCODER */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(DEB_A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ROT_SW_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles TIM5 global interrupt.
  */
void TIM5_IRQHandler(void)
{
  /* USER CODE BEGIN TIM5_IRQn 0 */

	/* For a given amount of time, keep temperatures stable */
	if ( tick_counter <  ( heat_time * 5)) {	// Keep in mind timer interrupts configured for 5 Hz.

			// DEBUG
			HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);

//			// Update temps
//			update_temps();

			// Update fan speed
			Controller_Update(&fan, 30.0, measured_amb_temp);
			PWM_Update(fan_pwm, TIM_CHANNEL_1, fan.out);

			// Update plate temperature
			Controller_Update(&hotplate, user_temp, measured_hotplate_temp);
			PWM_Update(hotplate_pwm, TIM_CHANNEL_1, hotplate.out);

		heat_complete = 0;
		tick_counter++;

	} else { 	// Else we must have reached tick count, reset counter

		tick_counter = 0;

		// Set heating cycle complete flag
		heat_complete = 1;

	}




  /* USER CODE END TIM5_IRQn 0 */
  HAL_TIM_IRQHandler(&htim5);
  /* USER CODE BEGIN TIM5_IRQn 1 */
  /* USER CODE END TIM5_IRQn 1 */
}


/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
