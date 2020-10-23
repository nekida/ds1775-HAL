#include "ds1775.h"

uint8_t ds1775_control_code 				= 0x9;
uint8_t ds1775_addr_reg_temperature	= 0x0;
uint8_t ds1775_slave_address				= 0x0;

float ds1775_get_temperature(void)
{
	float temperature = 0.0;
	uint8_t temper[2] = {0};
	uint8_t tmp[2] 		= {0};	
	int16_t tmp16			= 0;
	uint8_t ds1775_slave_address_read;
	uint8_t ds1775_slave_address_write;
	
	ds1775_slave_address = ( (ds1775_control_code  << 3) | (ds1775_addr_reg_temperature) );
	ds1775_slave_address_read 	= (ds1775_slave_address) << 1 | 0x1;
	ds1775_slave_address_write 	= (ds1775_slave_address) << 1 & 0x0;

	HAL_I2C_Master_Transmit(&hi2c1, ds1775_slave_address_write, &ds1775_addr_reg_temperature, 1, 100);
	HAL_I2C_Master_Receive(&hi2c1, ds1775_slave_address_read, temper, 2, 100);
	
	tmp[0] = temper[1];
	tmp[1] = temper[0];
	
	tmp16 = (tmp[0] | tmp[1] << 8);
	temperature = (float)tmp16;
	temperature *= DS1775_COEF_9BIT;
	
	return temperature;
}


