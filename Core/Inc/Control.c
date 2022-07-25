#include "Control.h"

void Controller_Init(PIController *sys)
{

	// Define controller variables
	sys->integrator = 0.0f;
	sys->prev_error = 0.0f;
	sys->prev_meas = 0.0f;
	sys->out = 0.0f;

}

float Controller_Update(PIController *sys, float setpoint, float measurement)
{

	float error, proportional;

	// Find error signal
	error = setpoint - measurement;

	// Calculate proportional term
	proportional = sys->Kp * error;

	// Calculate integral term
	sys->integrator = sys->integrator + 0.5f * sys->Ki * sys->T * (error + sys->prev_error);

	// Clamp integral term (saturating)
	if (sys->integrator > sys->lim_max_int) {

		sys->integrator = sys->lim_max_int;

	} else if (sys->integrator < sys->lim_min_int) {

		sys->integrator = sys->lim_min_int;
	}

	// Calculate controller output
	sys->out = proportional + sys->integrator;

	// Clamp controller output (saturating)
	if (sys->out > sys->lim_max) {

		sys->out = sys->lim_max;

	} else if (sys->out < sys->lim_min) {

		sys->out = sys->lim_min;

	}

	// Update prev values for next iteration
	sys->prev_error = error;
	sys->prev_meas = measurement;

	return sys->out;

}

//void Toggle_Heating(float plate_temp, int desired_temp)
//{
//
//	float error;
//
//	// Sign of difference determines whether plate is on or off
//	error = plate_temp - desired_temp;
//
//	// If temperature is higher than desired, turn off hotplate
//	if (error > 0) {
//
//		/* Turn off hotplate */
//		return;
//
//	} else if (error < 0) {	// If temperature is lower than desired, turn on hotplate
//
//		/* Turn on hotplate */
//		return;
//
//	} else { // Otherwise the temperature must be perfect
//
//		return;
//
//	}
//
//}
