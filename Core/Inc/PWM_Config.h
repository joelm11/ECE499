// For changing frequency and duty-cycle of PWM signals

#include <stdio.h>
#include <stdint.h>
#include "tim.h"

/* @brief Updates PWM duty-cycle
 * @param Timer where Timer is a pointer to timer struct with configured data
 * @param Timer_Channel where Timer_Channel is an unsigned 16-bit integer macro
 * @param Duty_Cycle may range from 0 to 0xFFFF and defines HI time of signal
 */
void PWM_Update(TIM_HandleTypeDef *Timer, uint16_t Timer_Channel, uint16_t Duty_Cycle);
