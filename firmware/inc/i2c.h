#ifndef I2C_H_
#define I2C_H_

#include <board.h>

#include <stddef.h>
#include <stm32f1xx_hal_i2c.h>
#include <stm32f1xx_hal_gpio_ex.h>

int i2c_init();
int i2c_de_init();
int i2c_read(uint8_t address, uint8_t * dest, size_t length);
int i2c_write(uint8_t address, uint8_t * src, size_t length);
int i2c_mem_read(uint8_t address, uint8_t mem_address, uint8_t *dest,
		size_t length);
int i2c_mem_write(uint8_t address, uint8_t mem_address, uint8_t *src,
		size_t length);

#endif /* I2C_H_ */
