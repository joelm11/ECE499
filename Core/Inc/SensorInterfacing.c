
#include "SensorInterfacing.h"


void read_ambient_temp(){

	const uint8_t tempr_reg = 0x00;
	const uint8_t ambient_sens_addr = 0x48 << 1;	// Note address needs to be shifted by 1 bit in this protocol
	uint8_t tempr_data_buff[2];
	int final_tempr = 0;

	HAL_I2C_Master_Transmit(hi2c, ambient_sens_addr, &tempr_reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(hi2c, ambient_sens_addr, tempr_data, 2, HAL_MAX_DELAY);
	final_tempr = (tempr_data_buff[0] << 8) | (tempr_data_buff[1] >> 4);

	return;
}
