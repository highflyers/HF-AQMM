#include <EEPROM.h>

int eeprom_read(parameters_t * params)
{
	uint8_t addr = 0;
	for (addr = 0; addr < params->size * sizeof(params->array[0]);
			addr +=	EEPROM_PAGE_SIZE)
	{
		eeprom_read_page(addr, ((uint8_t*) (params->array)) + addr);
	}
	return 0;
}

int eeprom_read_page(int addr, uint8_t *values)
{
	int ret = i2c_mem_read(eeprom_device_address(addr),
			eeprom_memory_address(addr), values, EEPROM_PAGE_SIZE);
	return ret;
}

int eeprom_write(parameters_t * params)
{
	uint8_t addr = 0;
	for (addr = 0; addr < params->size * sizeof(params->array[0]);
			addr +=	EEPROM_PAGE_SIZE)
	{
		eeprom_write_page(addr, ((uint8_t*) (params->array)) + addr);
	}
	return 0;
}

int eeprom_write_page(int addr, uint8_t *values)
{
	uint8_t arr[EEPROM_PAGE_SIZE+1];
	arr[0] = eeprom_memory_address(addr);
	for (int i = 0; i < EEPROM_PAGE_SIZE; ++i)
	{
		arr[i + 1] = values[i];
	}
	int ret = i2c_write(eeprom_device_address(addr), arr, EEPROM_PAGE_SIZE+1);
	HAL_Delay(100);
	return ret;
}

int eeprom_device_address(int memory_address)
{
	return EEPROM_DEVICE_BASE_ADDRESS | ((memory_address >> 8) & 0b111);
}

int eeprom_memory_address(int memory_address)
{
	return (memory_address & 0xFF);
}
