#include "PWM_Config.h"

// Update dutycycle of PWM signal. Frequency of PWM signal is hardcoded for now
void PWM_Update(TIM_HandleTypeDef *Timer, uint32_t Timer_Channel, float Duty_Cycle)
{
	uint16_t tim_period, ccr_val;

	tim_period = __HAL_TIM_GET_AUTORELOAD(Timer);

	// If requested DC is 0, turn PWM off
	if (Duty_Cycle == 0) {

		HAL_TIM_PWM_Stop(Timer, Timer_Channel);

		return;

	} else {

		ccr_val = Duty_Cycle * tim_period;

		// Catch undefined case where DC would be >= 100%
		if (ccr_val >= tim_period) {

			ccr_val = tim_period;	// Probably get rid of this

		}

		// Update PWM Duty Cycle
		__HAL_TIM_SET_COMPARE(Timer, Timer_Channel, ccr_val);

		// Ensure PWM is running
		HAL_TIM_PWM_Start(Timer, Timer_Channel);

	}

	return;

};

// Heat hotplate according to Wikipedia solder curve function
void PWM_Heat_Plate(volatile float user_temp, volatile float user_preheat_time, volatile float user_reflow_time)
{


	return;
}
