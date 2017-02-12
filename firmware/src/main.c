#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "stm32f1xx.h"

#include <SystemClock_Config.h>
#include <uart_usb.h>

#include <i2c.h>
#include <rgb_pwm.h>
#include <debug.h>
#include <adc.h>
#include <filter.h>
#include <button.h>
#include <params.h>
#include <EEPROM.h>
#include <DHTxx.h>

#define PARAMETERS_ARRAY_SIZE		12
#define STRING_BUFFER_SIZE			256

uint8_t flaga = 0;
volatile uint32_t adc_value[8];

char str[STRING_BUFFER_SIZE];

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	uart_usb_init();
	RGB_Pwm_Init();
	ADC1_Init();

	button_init();
	DHTxx_init();

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

	uint32_t DHTxx_READ_PERIOD	= 5000;
	uint32_t DHTxx_last_read = 0;

	int params_array[PARAMETERS_ARRAY_SIZE];
	parameters_t params;
	params.array = params_array;
	params.size = PARAMETERS_ARRAY_SIZE;

	eeprom_read(&params);

	int temperature, humidity, DHTxx_error = 100;

	while (1)
	{
		if (flaga == 1 && !(button_flip_flop_status & 1))
		{
			snprintf(str, STRING_BUFFER_SIZE, "%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%d\t%d\n",
					(uint32_t)temperature,(uint32_t)humidity,(uint32_t)DHTxx_error,
					adc_value[0],
					filter_new_data(&filter, adc_value[0] << 3) >> 3,
					adc_value[1], adc_value[2], adc_value[3], adc_value[4],
					adc_value[5], adc_value[6], adc_value[7],
					HAL_GPIO_ReadPin(BUTTON1_GPIO, BUTTON1_PIN),
					button_flip_flop_status);
			uart_usb_send_it(str, strlen(str));
			flaga = 0;
			DHTxx_error = 100;
		}
		if (HAL_GetTick() - patternLastUpdate >= RGP_PATTERN_PERIOD
				|| HAL_GetTick() - patternLastUpdate < 0)
		{
			RGB_Pattern_Update();
			patternLastUpdate = HAL_GetTick();
		}
		if (HAL_GetTick() - DHTxx_last_read >= DHTxx_READ_PERIOD
				|| HAL_GetTick() - DHTxx_last_read < 0)
		{
			DHTxx_error = DHTxx_read(&temperature, &humidity);
			DHTxx_last_read = HAL_GetTick();
		}
		if (button_flip_flop_status & 1)
		{
			RGB_Set_Pattern_Color(0, 1, 0);
		}
		else
		{
			RGB_Set_Pattern_Color(0, 0, 1);
		}
		if (uart_input_flag)
		{
			if (button_flip_flop_status & 1)
			{
				params_command(&params, uart_input_buffer);
				eeprom_write(&params);
				eeprom_read(&params);
				params_print(&params);
			}
			uart_input_flag = 0;
		}
	}
}
