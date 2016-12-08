#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "stm32f1xx.h"

#include <SystemClock_Config.h>
#include <uart_usb.h>
#include "rgb_pwm.h"
#include "debug.h"
#include "adc.h"
#include "filter.h"
#include "button.h"

uint8_t flaga = 0;
volatile uint32_t adc_value[8];

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	uart_usb_init();
	RGB_Pwm_Init();
	ADC1_Init();

	button_init();

	filter_t filter;
	filter.coeffs_a_size = 1;
	filter.coeffs_a = malloc(1 * sizeof(uint32_t));
	filter.coeffs_a[0] = 256;
	filter.coeffs_b_size = 1;
	filter.coeffs_b = malloc(1 * sizeof(uint32_t));
	filter.coeffs_b[0] = 1024;
	filter.input_history = malloc(1 * sizeof(uint32_t));
	filter.input_history_size = 1;
	filter.output_history = malloc(1 * sizeof(uint32_t));
	filter.output_history_size = 1;

	filter_reset(&filter, 0);
	RGB_Set_Pattern_Color(0, 1, 0);

	uint32_t patternLastUpdate = 0;

	while (1)
	{
		if (flaga == 1)
		{
			//display adc values
			debug("%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%d\t%d\n", adc_value[0],
					filter_new_data(&filter, adc_value[0]<<3)>>3, adc_value[1],
					adc_value[2], adc_value[3], adc_value[4], adc_value[5],
					adc_value[6], adc_value[7], HAL_GPIO_ReadPin(BUTTON1_GPIO, BUTTON1_PIN), button_flip_flop_status);
			flaga = 0;
		}
		if (HAL_GetTick() - patternLastUpdate >= RGP_PATTERN_PERIOD
				|| HAL_GetTick() - patternLastUpdate < 0)
		{
			RGB_Pattern_Update();
			patternLastUpdate = HAL_GetTick();
		}
		if (button_flip_flop_status & 1)
		{
			RGB_Set_Pattern_Color(0, 1, 0);
		}
		else
		{
			RGB_Set_Pattern_Color(0, 0, 1);
		}
	}
}
