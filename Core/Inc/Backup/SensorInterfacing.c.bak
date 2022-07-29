//
//#include "SensorInterfacing.h"
//
//// NOTE THIS IS NOW IMPLEMENTED IN i2c.c !!!!!!!
////int read_ambient_temp(){
////
////	uint8_t tempr_reg = 0x00;
////	uint8_t ambient_sens_addr = 0x48 << 1;	// Note address needs to be shifted by 1 bit in this protocol
////	uint8_t tempr_data_buff[2];
////	int final_tempr = 0;
////
////	HAL_I2C_Master_Transmit(&hi2c1, ambient_sens_addr, &tempr_reg, 1, 500);
////	HAL_I2C_Master_Receive(&hi2c1, ambient_sens_addr, tempr_data_buff, 2, 500);
////	final_tempr = (tempr_data_buff[0] << 8) | (tempr_data_buff[1] >> 4);
////
////	return final_tempr;
////}
