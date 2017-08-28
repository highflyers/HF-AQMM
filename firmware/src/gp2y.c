#include <gp2y.h>
#include <board.h>

#include <stm32f1xx.h>
#include <stm32f1xx_hal_gpio.h>
#include <stm32f1xx_hal_gpio_ex.h>

void gp2y_init()
{
	GPIO_InitTypeDef g;

	GP2Y_EN_GPIO_CLK_ENABLE();
	g.Mode = GPIO_MODE_AF_PP;
//	g.Mode = GPIO_MODE_OUTPUT_PP;
	g.Pull = GPIO_NOPULL;
	g.Speed = GPIO_SPEED_FREQ_HIGH;
	g.Pin = GP2Y_EN_GPIO_PIN;
	HAL_GPIO_Init(GP2Y_EN_GPIO, &g);
	HAL_GPIO_WritePin(GP2Y_EN_GPIO, GP2Y_EN_GPIO_PIN, GPIO_PIN_SET);

//	RGB_Timer3_Init();
	TIM3->CCR3 = 320;
}
