// Credit to Philip Salmony for the control code
// https://www.youtube.com/watch?v=zOByx3Izf5U
typedef struct PIController {

	// Proportional gain
	float Kp;
	// Integral gain
	float Ki;

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
