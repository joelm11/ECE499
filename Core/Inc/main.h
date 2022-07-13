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
#ifndef __MAIN_H
#define __MAIN_H

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

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define EN_12V_Pin GPIO_PIN_13
#define EN_12V_GPIO_Port GPIOC
#define LCD_PWM_Pin GPIO_PIN_1
#define LCD_PWM_GPIO_Port GPIOC
#define BUCK_PWM_Pin GPIO_PIN_0
#define BUCK_PWM_GPIO_Port GPIOA
#define FAN_PWM_Pin GPIO_PIN_2
#define FAN_PWM_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_3
#define LCD_CS_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_4
#define LCD_DC_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_6
#define LCD_RST_GPIO_Port GPIOA
#define SENS_DIS_Pin GPIO_PIN_4
#define SENS_DIS_GPIO_Port GPIOC
#define DISP_DIS_Pin GPIO_PIN_5
#define DISP_DIS_GPIO_Port GPIOC
#define TEMP_INT_Pin GPIO_PIN_0
#define TEMP_INT_GPIO_Port GPIOB
#define IMU_INT1_Pin GPIO_PIN_1
#define IMU_INT1_GPIO_Port GPIOB
#define IMU_INT2_Pin GPIO_PIN_2
#define IMU_INT2_GPIO_Port GPIOB
#define DEB_B_Pin GPIO_PIN_13
#define DEB_B_GPIO_Port GPIOB
#define DEB_A_Pin GPIO_PIN_14
#define DEB_A_GPIO_Port GPIOB
#define ROT_SW_Pin GPIO_PIN_15
#define ROT_SW_GPIO_Port GPIOB
#define LED_R_Pin GPIO_PIN_7
#define LED_R_GPIO_Port GPIOC
#define LED_G_Pin GPIO_PIN_8
#define LED_G_GPIO_Port GPIOC
#define LED_B_Pin GPIO_PIN_9
#define LED_B_GPIO_Port GPIOC
#define PLATE_PWM_Pin GPIO_PIN_8
#define PLATE_PWM_GPIO_Port GPIOA
#define SEL_0_Pin GPIO_PIN_10
#define SEL_0_GPIO_Port GPIOA
#define SEL_1_Pin GPIO_PIN_11
#define SEL_1_GPIO_Port GPIOA
#define PG_3V3_Pin GPIO_PIN_15
#define PG_3V3_GPIO_Port GPIOA
#define BUZZ_PWM_Pin GPIO_PIN_12
#define BUZZ_PWM_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
