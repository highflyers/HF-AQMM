#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stm32f1xx.h"

#include <SystemClock_Config.h>
#include <uart_usb.h>
#include "rgb_pwm.h"
#include "debug.h"
#include "filter.h"

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	uart_usb_init();
	RGB_Pwm_Init();

	filter_t filter;
	filter.coeffs_a_size = 1;
	filter.coeffs_a = malloc(1*sizeof(uint32_t));
	filter.coeffs_a[0] = 500;
	filter.coeffs_b_size = 1;
	filter.coeffs_b = malloc(1*sizeof(uint32_t));
	filter.coeffs_b[0] = 3596;
	filter.input_history = malloc(1*sizeof(uint32_t));
	filter.input_history_size = 1;
	filter.output_history = malloc(1*sizeof(uint32_t));
	filter.output_history_size = 1;

	filter_reset(&filter, 0);
	RGB_Set_Pattern_Color(1,0,1);

	int n = 0;
	while (1)
	{
		RGB_Pattern_Update();
		if (n % 100 == 0)
		{
			++n;
			// input test data
			debug("%d, %lu\n", 3700 + (n>>2)%600, filter_new_data(&filter, 3700 + ((n>>2)%600)));
		}
		++n;
		HAL_Delay(10);
	}
}
