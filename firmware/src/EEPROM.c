#include <EEPROM.h>

int eeprom_read(parameters_t * params)
{
	int ret = i2c_mem_read(eeprom_device_address(0), eeprom_memory_address(0), (uint8_t*)(params->array), 16);
	HAL_Delay(100);
	return ret;
}

int eeprom_write_page(int addr, uint8_t *values)
{
	uint8_t arr[17];
	arr[0] = addr;
	for(int i = 0; i < 16; ++i)
	{
		arr[i+1] = values[i];
	}
	return i2c_write(eeprom_device_address(addr), arr, 17);
}

int eeprom_write(parameters_t * params)
{
	uint8_t addr = 0;
	for (addr = 0; addr < params->size*sizeof(params->array[0]); addr += EEPROM_PAGE_SIZE)
	{
		eeprom_write_page(addr, ((uint8_t*)(params->array))+addr);
	}
	return 0;
}

int eeprom_device_address(int memory_address)
{
	return EEPROM_DEVICE_BASE_ADDRESS + (memory_address / EEPROM_PAGE_SIZE) + 1;
}

int eeprom_memory_address(int memory_address)
{
	return (memory_address % EEPROM_PAGE_SIZE);
}
