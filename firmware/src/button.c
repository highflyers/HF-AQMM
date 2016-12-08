#include <board.h>
#include <button.h>
#include <stm32f1xx_hal_gpio.h>

volatile int button_flip_flop_status;

void button_init()
{
	BUTTON1_GPIO_RCC_ENABLE();

	GPIO_InitTypeDef g;
	g.Mode = GPIO_MODE_IT_RISING;
	g.Pin = BUTTON1_PIN;
	g.Pull = GPIO_PULLDOWN;
	g.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(BUTTON1_GPIO, &g);

	button_flip_flop_status = 0;

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 6, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void button_callback()
{
	button_flip_flop_status ^= 1;
}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	button_callback();
}

void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(BUTTON1_PIN);
}

