#include <stdio.h>
#include <string.h>

#include "stm32f1xx.h"

#include <SystemClock_Config.h>
#include <uart_usb.h>
#include "rgb_pwm.h"


int main(void)
{
	HAL_Init();
	SystemClock_Config();

	uart_usb_init();
	RGB_Pwm_Init();

	char str[1024];
	int n = 0;
	while (1)
	{
		// Set led Duty Cycle in %
		RGB_Set_PulseWidth(LED_R, 75);
		snprintf(str, 1024, "%d\n", ++n);
		//uart_usb_send(str, strlen(str));
		HAL_UART_Transmit(&uart_usb_handle, (uint8_t*)str, strlen(str), 1000);

		HAL_Delay(500);
	}
}
