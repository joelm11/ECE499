// For changing frequency and duty-cycle of PWM signals

#include <stdio.h>
#include <stdint.h>
#include "tim.h"
#include "main.h"

/* @brief Updates PWM duty-cycle
 * @param Timer where Timer is a pointer to timer struct with configured data
 * @param Timer_Channel where Timer_Channel is an unsigned 16-bit integer macro
 * @param Duty_Cycle may range from 0 to 1 and defines HI time of signal
 */
void PWM_Update(TIM_HandleTypeDef *Timer, uint32_t Timer_Channel, float Duty_Cycle);


/* @brief Updates PWM duty-cycle
 * @param Timer where Timer is a pointer to timer struct with configured data
 * @param Timer_Channel where Timer_Channel is an unsigned 16-bit integer macro
 * @param Duty_Cycle may range from 0 to 1 and defines HI time of signal
 */
void PWM_Heat_Plate(volatile float user_temp, volatile float user_preheat_time, volatile float user_reflow_time);

// Ramp temp to preheat level
// Hold preheat level for xxx seconds
// Ramp temp to reflow level
// Hold reflow level for xxx seconds
// Turn off

// PWM_Update 100% until desired temp hit
// Run control loop at regular intervals until xxx seconds to maintain temp
// PWM_Update 100% until desired temp hit
// Run control loop at regulat intervals until xxx seconds to maintain temp
