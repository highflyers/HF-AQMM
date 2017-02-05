#ifndef EEPROM_H_
#define EEPROM_H_

#include <params.h>
#include <i2c.h>

#define EEPROM_DEVICE_BASE_ADDRESS		0b10100000

/**
 * Reads parameters from external memory into struct.
 * 'params' must be a valid structure containing number of parameters to read
 */
int eeprom_read(parameters_t * params);

int eeprom_write(parameters_t * params);

int eeprom_device_address(int memory_address);
int eeprom_memory_address(int memory_address);

#endif /* EEPROM_H_ */
