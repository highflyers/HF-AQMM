#include <EEPROM.h>

int eeprom_read(parameters_t * params)
{
	uint8_t arr[16];
	return i2c_mem_read(eeprom_device_address(0), eeprom_memory_address(0), arr, 16);
}

int eeprom_write(parameters_t * params)
{
	return 0;
}

int eeprom_device_address(int memory_address)
{
	return EEPROM_DEVICE_BASE_ADDRESS;
}

int eeprom_memory_address(int memory_address)
{
	return 0;
}
