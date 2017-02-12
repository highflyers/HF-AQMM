#include <DHTxx.h>

void DHTxx_init()
{
	DHTxx_GPIO_CLK_ENABLE();
	DHTxx_up();
	GPIO_InitTypeDef g;
	g.Mode = GPIO_MODE_OUTPUT_OD;
	g.Pull = GPIO_NOPULL;
	g.Speed = GPIO_SPEED_FREQ_HIGH;
	g.Pin = DHTxx_GPIO_PIN;
	HAL_GPIO_Init(DHTxx_GPIO, &g);
}

int DHTxx_read(int *T, int *RH)
{
	uint8_t RH_high, RH_low, T_high, T_low, checksum;
	DHTxx_start();
	uint32_t time = DHTxx_wait_for_ready();
	if(time >= DHTxx_TIMEOUT)
	{
		return DHTxx_ERROR_TIMEOUT;
	}
	RH_high =  DHTxx_read_byte();
	RH_low =  DHTxx_read_byte();
	T_high =  DHTxx_read_byte();
	T_low =  DHTxx_read_byte();
	checksum =  DHTxx_read_byte();
	if(checksum == (RH_high + RH_low + T_high + T_low))
	{
		*RH = ((RH_high << 8) | RH_low);
		*T = ((T_high << 8) | T_low);
		return DHTxx_ERROR_OK;
	}
	else
	{
		return DHTxx_ERROR_CHECKSUM;
	}
}

void DHTxx_start()
{
	DHTxx_up();
	DHTxx_down();
	HAL_Delay(5);
	DHTxx_up();
}

uint8_t DHTxx_read_byte()
{
	uint8_t byte = 0;
	for(int i = 0; i < 8; ++i)
	{
		byte |= DHTxx_read_bit();
		byte <<= 1;
	}
	return byte;
}

uint32_t DHTxx_wait_for_ready()
{
	uint32_t time = 0;
	time = DHTxx_wait_for_low();
	if(time < DHTxx_TIMEOUT)
	{
		time = DHTxx_wait_for_high();
	}
	return time;
}

uint32_t DHTxx_read_bit()
{
	uint32_t time = DHTxx_read_signal_length();
	return time > DHTxx_THRESHOLD ? 1 : 0;
}

uint32_t DHTxx_read_signal_length()
{
	uint32_t time = 0;
	DHTxx_wait_for_low();
	time = DHTxx_wait_for_high();
	if(time < DHTxx_TIMEOUT)
	{
		time = DHTxx_wait_for_low();
	}
	return time;
}

void DHTxx_up()
{
	HAL_GPIO_WritePin(DHTxx_GPIO, DHTxx_GPIO_PIN, GPIO_PIN_SET);
}

void DHTxx_down()
{
	HAL_GPIO_WritePin(DHTxx_GPIO, DHTxx_GPIO_PIN, GPIO_PIN_RESET);
}

uint32_t DHTxx_wait_for_low()
{
	uint32_t time = 0;
	while(HAL_GPIO_ReadPin(DHTxx_GPIO, DHTxx_GPIO_PIN) != GPIO_PIN_RESET && time < DHTxx_TIMEOUT)
	{
		++time;
	}
	return time;
}

uint32_t DHTxx_wait_for_high()
{
	uint32_t time = 0;
	while(HAL_GPIO_ReadPin(DHTxx_GPIO, DHTxx_GPIO_PIN) != GPIO_PIN_SET && time < DHTxx_TIMEOUT)
	{
		++time;
	}
	return time;
}

void DHTxx_sleep(int delay)
{
	volatile int i = 0;
	for (i = 0; i < delay; ++i)
	{
	}
}
