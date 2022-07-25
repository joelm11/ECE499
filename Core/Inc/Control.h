// Credit to Philip Salmony for the control code
// https://www.youtube.com/watch?v=zOByx3Izf5U
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

void Controller_Init(PIController *sys);

float Controller_Update(PIController *sys, float setpoint, float measurement);

void Toggle_Heating(int plate_temp, int desired_temp);
