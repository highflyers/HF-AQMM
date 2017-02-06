#include <i2c.h>
#include <stm32f1xx.h>
#include <stm32f1xx_hal_gpio.h>
#include <stm32f1xx_hal_gpio_ex.h>

static I2C_HandleTypeDef i2c_handle;

int i2c_init()
{
	GPIO_InitTypeDef g;

	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_AFIO_REMAP_I2C1_ENABLE();

	I2C1_CLK_ENABLE();

	I2C1_SDA_GPIO_CLK_ENABLE();
	I2C1_SCL_GPIO_CLK_ENABLE();

	g.Mode = GPIO_MODE_OUTPUT_OD;
	g.Pull = GPIO_PULLUP;
	g.Speed = GPIO_SPEED_FREQ_HIGH;
	g.Pin = I2C1_SDA_GPIO_PIN | I2C1_SCL_GPIO_PIN;
	HAL_GPIO_Init(I2C1_SDA_GPIO_REG, &g);

	HAL_GPIO_WritePin(GPIOB, I2C1_SDA_GPIO_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, I2C1_SCL_GPIO_PIN, GPIO_PIN_SET);
	HAL_Delay(100);
	while(HAL_GPIO_ReadPin(GPIOB, I2C1_SDA_GPIO_PIN) != GPIO_PIN_SET || HAL_GPIO_ReadPin(GPIOB, I2C1_SCL_GPIO_PIN) != GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, I2C1_SDA_GPIO_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, I2C1_SCL_GPIO_PIN, GPIO_PIN_RESET);
	HAL_Delay(100);
	while(HAL_GPIO_ReadPin(GPIOB, I2C1_SDA_GPIO_PIN) != GPIO_PIN_RESET || HAL_GPIO_ReadPin(GPIOB, I2C1_SCL_GPIO_PIN) != GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, I2C1_SDA_GPIO_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, I2C1_SCL_GPIO_PIN, GPIO_PIN_SET);
	HAL_Delay(100);
	while(HAL_GPIO_ReadPin(GPIOB, I2C1_SDA_GPIO_PIN) != GPIO_PIN_SET || HAL_GPIO_ReadPin(GPIOB, I2C1_SCL_GPIO_PIN) != GPIO_PIN_SET);

	g.Mode = GPIO_MODE_AF_OD;
	HAL_GPIO_Init(I2C1_SDA_GPIO_REG, &g);

	I2C1->CR1 |= I2C_CR1_SWRST;
	HAL_Delay(100);
	I2C1->CR1 &= ~I2C_CR1_SWRST;

	i2c_handle.Instance = I2C1_REG;
	i2c_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c_handle.Init.ClockSpeed = 88000;
	i2c_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	i2c_handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
	i2c_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	i2c_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	i2c_handle.Init.OwnAddress1 = 0xAA;
	i2c_handle.Init.OwnAddress2 = 0xAA;
	int ret = HAL_I2C_Init(&i2c_handle);

	while(!(HAL_I2C_GetState(&i2c_handle) == HAL_I2C_STATE_READY))
	{
	}
	return ret;
}

int i2c_de_init()
{
	I2C1_CLK_DISABLE();
	return HAL_I2C_DeInit(&i2c_handle);
}

int i2c_read(uint8_t address, uint8_t * dest, size_t length)
{
	return HAL_I2C_Master_Receive(&i2c_handle, address, dest, length,
			HAL_MAX_DELAY);
}

int i2c_write(uint8_t address, uint8_t * src, size_t length)
{
	return HAL_I2C_Master_Transmit(&i2c_handle, address, src, length,
			HAL_MAX_DELAY);
}

int i2c_mem_read(uint8_t address, uint8_t mem_address, uint8_t *dest,
		size_t length)
{
	i2c_init();
//	int ret = HAL_I2C_Mem_Read(&i2c_handle, address, mem_address,
//			I2C_MEMADD_SIZE_8BIT, dest, length, HAL_MAX_DELAY);
	int ret = i2c_write(address, &mem_address, 1);
	i2c_de_init();
	return ret;
}

int i2c_mem_write(uint8_t address, uint8_t mem_address, uint8_t *src,
		size_t length)
{
	return HAL_I2C_Mem_Write(&i2c_handle, address, mem_address,
			I2C_MEMADD_SIZE_8BIT, src, length, HAL_MAX_DELAY);
}
