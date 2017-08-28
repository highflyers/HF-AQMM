/*
 * rgb_pwm.c
 *
 *  Created on: 26 lis 2016
 *      Author: Karollo
 */
#include "rgb_pwm.h"
#include "stm32f1xx_hal.h"
#include "uart_usb.h"

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

static uint8_t _r, _g, _b;
static uint32_t _value, _delta;

void RGB_Pwm_Gpio_Init()
{
	LED_GPIO_RCC_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

	//LED_B pin
	__HAL_RCC_AFIO_CLK_ENABLE();
	AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_1;
	GPIO_InitStruct.Pin = LED_B_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_B_GPIO, &GPIO_InitStruct);

    //LED_R
    GPIO_InitStruct.Pin = LED_R_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_R_GPIO, &GPIO_InitStruct);

    //LED_G
    GPIO_InitStruct.Pin = LED_G_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_G_GPIO, &GPIO_InitStruct);
}

void RGB_Timer3_Init()
{
	__HAL_RCC_TIM3_CLK_ENABLE();
	TIM_ClockConfigTypeDef sClockSourceConfig;
	  TIM_MasterConfigTypeDef sMasterConfig;
	  TIM_OC_InitTypeDef sConfigOC;

	  htim3.Instance = TIM3;
	  htim3.Init.Prescaler = 24;
	  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim3.Init.Period = 9999;
	  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	  {
	    //Error_Handler();
	  }

	  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	  {
	    //Error_Handler();
	  }

	  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
	  {
	    //Error_Handler();
	  }

	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	  {
	    //Error_Handler();
	  }

	  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	  sConfigOC.Pulse = 2499;
	  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	  {
	    //Error_Handler();
	  }
	  HAL_TIM_Base_Start(&htim3);
	  HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_2);

	  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	  sConfigOC.Pulse = 2499;
	  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	  {
	    //Error_Handler();
	  }
	  HAL_TIM_Base_Start(&htim3);
	  HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_3);
}

void RGB_Timer4_Init() {
	/* Peripheral clock enable */
	__HAL_RCC_TIM4_CLK_ENABLE()
	;

	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;

	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 24;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = PWM_PERIOD;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_PWM_Init(&htim4);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 2499;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);

	HAL_TIM_Base_Start(&htim4);

	HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_2);

}

void RGB_Pwm_Init()
{
	RGB_Pwm_Gpio_Init();
	RGB_Timer3_Init();
	RGB_Timer4_Init();
}

void RGB_Set_PulseWidth(LED_TypeDef led, uint8_t pulseWidth)
{
	__IO uint32_t *ocr = &TIM4->CCR1;
	switch(led)
	{
		case LED_R:
			ocr = &TIM4->CCR1;
			break;
		case LED_G:
			ocr = &TIM4->CCR2;
			break;
		case LED_B:
			ocr = &TIM3->CCR2;
			break;
	}
	if(pulseWidth > 255)
		pulseWidth = 255;

	if(pulseWidth < 0)
		pulseWidth = 0;

	*ocr = pulseWidth*PWM_PERIOD/255;
}

void RGB_Set_Color(uint8_t R, uint8_t G, uint8_t B)
{
	RGB_Set_PulseWidth(LED_R, R);
	RGB_Set_PulseWidth(LED_G, G);
	RGB_Set_PulseWidth(LED_B, B);
}

void RGB_Set_Pattern_Color(uint8_t R, uint8_t G, uint8_t B)
{
	_r = R > 0;
	_g = G > 0;
	_b = B > 0;
}

void RGB_Pattern_Update()
{
	_value += _delta;
	if (_value >= RGB_PATTERN_MAX)
	{
		_delta = -RGB_PATTERN_DELTA;
	}
	else if (_value <= RGB_PATTERN_MIN)
	{
		_delta = RGB_PATTERN_DELTA;
	}
	RGB_Set_Color(_value * _r, _value * _g, _value * _b);
}


