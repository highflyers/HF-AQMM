#include <stdio.h>
#include <string.h>

#include "stm32f1xx.h"

#include <SystemClock_Config.h>
#include <uart_usb.h>


int main(void)
{
	HAL_Init();
	SystemClock_Config();

	uart_usb_init();

	char str[1024];
	int n = 0;
	while (1)
	{
		snprintf(str, 1024, "%d\n", ++n);
		uart_usb_send(str, strlen(str));
		HAL_Delay(500);
	}
}
