#include <sensors_control.h>

void sensors_control_init()
{
	MQ131_EN_GPIO_CLK_ENABLE();
	TGS1_EN_GPIO_CLK_ENABLE();
	TGS2_EN_GPIO_CLK_ENABLE();

	GPIO_InitTypeDef g;
	g.Mode = GPIO_MODE_OUTPUT_PP;
	g.Pull = GPIO_PULLUP;
	g.Speed = GPIO_SPEED_FREQ_MEDIUM;

	g.Pin = MQ131_EN_GPIO_PIN;
	HAL_GPIO_Init(MQ131_EN_GPIO, &g);
	HAL_GPIO_WritePin(MQ131_EN_GPIO, MQ131_EN_GPIO_PIN, GPIO_PIN_RESET);

	g.Pin = TGS1_EN_GPIO_PIN;
	HAL_GPIO_Init(TGS1_EN_GPIO, &g);
	HAL_GPIO_WritePin(TGS1_EN_GPIO, TGS1_EN_GPIO_PIN, GPIO_PIN_RESET);

	g.Pin = TGS2_EN_GPIO_PIN;
	HAL_GPIO_Init(TGS2_EN_GPIO, &g);
	HAL_GPIO_WritePin(TGS2_EN_GPIO, TGS2_EN_GPIO_PIN, GPIO_PIN_RESET);
}

void sensors_control_enable(int sensor)
{
	HAL_GPIO_WritePin(sensors_control_gpio(sensor), sensors_control_pin(sensor), GPIO_PIN_SET);
}

void sensors_control_disable(int sensor)
{
	HAL_GPIO_WritePin(sensors_control_gpio(sensor), sensors_control_pin(sensor), GPIO_PIN_RESET);
}

void sensors_control_enable_all()
{
	for(int i = 0; i < SENSOR_CONTROL_NUMBER_OF_SENSORS; ++i)
	{
		sensors_control_enable(i);
	}
}

void sensors_control_disable_all()
{
	for(int i = 0; i < SENSOR_CONTROL_NUMBER_OF_SENSORS; ++i)
	{
		sensors_control_disable(i);
	}
}

GPIO_TypeDef *sensors_control_gpio(int sensor)
{
	switch(sensor)
	{
	case SENSOR_MQ131:
		return MQ131_EN_GPIO;
		break;
	case SENSOR_TGS1:
		return TGS1_EN_GPIO;
		break;
	case SENSOR_TGS2:
		return TGS2_EN_GPIO;
		break;
	default:
		return 0;
		break;
	}
}

uint16_t sensors_control_pin(int sensor)
{
	switch(sensor)
	{
	case SENSOR_MQ131:
		return MQ131_EN_GPIO_PIN;
		break;
	case SENSOR_TGS1:
		return TGS1_EN_GPIO_PIN;
		break;
	case SENSOR_TGS2:
		return TGS2_EN_GPIO_PIN;
		break;
	default:
		return 0;
		break;
	}
}
