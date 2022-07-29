/*	Implementation of discrete Proportional-Integral (PI) Closed-Loop Control
 * 	Controller is encapsulated within PIController type and initialized with Controller_Init()
 * 	Controller output is computed within the struct when Controller_Update is provided a setpoint and measurement
 *
 *  TODO: Look into implementing derivative control for this system as it may benefit (?)
 *  Credit to Philip Salmony for his implementation of PID control
 *  https://www.youtube.com/watch?v=zOByx3Izf5U	https://github.com/pms67/PID.git
*/

#include "main.h"

/* Calculated constants for hotplate control loop */
#define PLATE_KP  3.0f
#define PLATE_KI  1.0f
#define PLATE_LIM_MIN 0.0f
#define PLATE_LIM_MAX  1.0f
#define PLATE_LIM_MIN_INT 1.0f	// Setting these to half the max output of 1.0
#define PLATE_LIM_MAX_INT -1.0f	// Setting these to half the max output of 1.0
#define PERIOD 0.2f				// Hardcoded for now (TIM5 IT Frequency)

/* Calculated constants for fan control loop */
#define FAN_KP  3.0f
#define FAN_KI  1.0f
#define FAN_LIM_MIN 0.2f
#define FAN_LIM_MAX  1.0f
#define FAN_LIM_MIN_INT 1.0f	// Setting these to half the max output of 1.0
#define FAN_LIM_MAX_INT -1.0f	// Setting these to half the max output of 1.0

/* Calculated constants for fan control loop */
typedef struct PIController{

	// Proportional gain
	float Kp;

	// Integral gain
	float Ki;

	// Integrator limits
	float lim_min_int;
	float lim_max_int;

	// Output limits
	float lim_min;
	float lim_max;

	// Period
	float T;

	// Controller variables
	float integrator;
	float prev_error;
	float prev_meas;

	// Controller output
	float out;

} PIController;

/*	@brief Initialize controller stored variables to 0
 */
void Controller_Init(PIController *sys);

/* @brief Calculate controller output
*  @param *sys pointer to PI system
*  @param setpoint system desired setpoint
*  @param measurement current system state
*/
float Controller_Update(PIController *sys, float setpoint, float measurement);

/* @brief Naive temperature control by toggling element
*  @param plate_temp Current hotplate temperature
*  @param desired_temp User set temperature
*/
void Toggle_Heating(float plate_temp, int desired_temp);

/* START ZN TUNING ROUTINE
 * @brief Find oscillation for ZN calculation of controller gains
 *
 *

	  // Start hotplate at 50% Duty Cycle
	HAL_TIM_PWM_Start(hotplate_pwm, TIM_CHANNEL_1);
	PWM_Update(hotplate_pwm, TIM_CHANNEL_1, .5);

	// Set integral gain to 0
	sys->Ki = 0;

	while (1) {

		// Use the user temp to configure KP gain
		sys->Kp = user_temp;

		// Observe temperature response
		LCD_updt_temps(&measured_hotplate_temp, &measured_amb_temp);
		LCD_Refresh(2);
		update_temps();
		HAL_Delay(500);
	}

 END ZN TUNING ROUTINE */





