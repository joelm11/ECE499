// For changing frequency and duty-cycle of PWM signals

#include <stdio.h>
#include <stdint.h>
#include "tim.h"

/* @brief Updates PWM duty-cycle
 * @param Timer where Timer is a pointer to timer struct with configured data
 * @param Timer_Channel where Timer_Channel is an unsigned 16-bit integer macro
 * @param Duty_Cycle may range from 0 to 1 and defines HI time of signal
 */
void PWM_Update(TIM_HandleTypeDef *Timer, uint32_t Timer_Channel, float Duty_Cycle);

// Timer counts to .Period to turn on and .Pulse to turn off
// !! .Period needs to be larger than .Pulse !!
// Base timer clock is 16 MHz, period for PWM is TRise1 - TRise2
// NOTE: Frequency is probably something we hardcode manually
void PWM_Updatef(TIM_HandleTypeDef *Timer, uint32_t Timer_Channel, uint32_t Frequency);
