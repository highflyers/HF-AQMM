#include <stdio.h>
#include <string.h>

#include "stm32f1xx.h"

#include <SystemClock_Config.h>
#include <uart_usb.h>
#include "rgb_pwm.h"
#include "debug.h"
#include "adc.h"

uint8_t flaga = 0;
volatile uint32_t adc_value[8];

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	uart_usb_init();
	RGB_Pwm_Init();
	ADC1_Init();

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
			//debug("%d\n", n);
		}
		pulse += delta;
		++n;
		HAL_Delay(10);
		//display adc values
		if(flaga == 1){
			debug("%lu	%lu	%lu	%lu	%lu	%lu	%lu	%lu\n", adc_value[0], adc_value[1], adc_value[2], adc_value[3], adc_value[4], adc_value[5], adc_value[6], adc_value[7]);
			flaga = 0;
		}
	}
}
