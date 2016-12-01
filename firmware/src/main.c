#include <stdio.h>
#include <string.h>

#include "stm32f1xx.h"

#include <SystemClock_Config.h>
#include <uart_usb.h>
#include "rgb_pwm.h"
#include "debug.h"

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	uart_usb_init();
	RGB_Pwm_Init();

	int n = 0;
	int pulse = 0;
	int delta = 1;
	while (1)
	{
		// Set led Duty Cycle in %
		RGB_Set_PulseWidth(LED_R, pulse % 100);
		RGB_Set_PulseWidth(LED_G, 100 - (pulse % 100));
		RGB_Set_PulseWidth(LED_B, 100 - (pulse % 100));
		if (pulse >= 95)
		{
			delta = -1;
		}
		else if (pulse <= 5)
		{
			delta = 1;
		}
		if (n % 100 == 0)
		{
			++n;
			debug("%d\n", n);
		}
		pulse += delta;
		++n;
		HAL_Delay(10);
	}
}
