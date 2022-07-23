#include "PWM_Config.h"

void PWM_Update(TIM_HandleTypeDef *Timer, uint16_t Timer_Channel, uint16_t Duty_Cycle)
{
	TIM_OC_InitTypeDef sConfigOC = {0};
	HAL_TIM_PWM_Stop(Timer, Timer_Channel);
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = Duty_Cycle;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(Timer, &sConfigOC, Timer_Channel);
	HAL_TIM_PWM_Start(Timer, Timer_Channel);
};
