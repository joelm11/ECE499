#include "PWM_Config.h"

void PWM_Update(TIM_HandleTypeDef *Timer, uint32_t Timer_Channel, float Duty_Cycle)
{

	TIM_OC_InitTypeDef sConfigOC = {0};
	HAL_TIM_PWM_Stop(Timer, Timer_Channel);
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	uint16_t temp = (uint16_t)(Duty_Cycle * (1 << 16) - 1);	// Testing
	sConfigOC.Pulse = temp;	// Convert to integer
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(Timer, &sConfigOC, Timer_Channel);
	HAL_TIM_PWM_Start(Timer, Timer_Channel);

};

void PWM_Updatef(TIM_HandleTypeDef *Timer, uint32_t Timer_Channel, uint32_t Frequency)
{

	return;
};
