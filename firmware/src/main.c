#include "stm32f1xx.h"

#include <SystemClock_Config.h>

#include <uart_usb.h>

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	uart_usb_init();

	uint8_t str[] =
	{ 48, 49, 50, 51, 52 };
	while (1)
	{
		HAL_UART_Receive(&uart_usb_handle, str, 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&uart_usb_handle, str, 1, HAL_MAX_DELAY);
	}
}
