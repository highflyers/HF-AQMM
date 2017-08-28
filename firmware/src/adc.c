/*
 * adc.c
 *
 *  Created on: 1 gru 2016
 *      Author: Karollo
 */

#include "adc.h"
#include "stm32f1xx.h"
#include "debug.h"
#include <peak_detector.h>

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
uint32_t sample[8] = {1,1,1,1,1,1,1,1};
volatile uint32_t adc_value[8];
extern uint8_t flaga, gp2y_should_reset;

void ADC1_Periph_Init() {
	/* Peripheral clock enable */
	__HAL_RCC_ADC1_CLK_ENABLE();

	ADC_ChannelConfTypeDef sConfig;

	/**Common config
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 8;
	if (HAL_ADC_Init(&hadc1) != HAL_OK) {
		while(1);
	}

	/**Configure Regular Channels
	 */
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		while(1);
	}

	sConfig.Channel = ADC_CHANNEL_2;
	sConfig.Rank = 2;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		while(1);
	}

	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = 3;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		while(1);
	}

	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 4;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		while(1);
	}

	sConfig.Channel = ADC_CHANNEL_10;
	sConfig.Rank = 5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		while(1);
	}

	sConfig.Channel = ADC_CHANNEL_12;
	sConfig.Rank = 6;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		while(1);
	}

	sConfig.Channel = ADC_CHANNEL_14;
	sConfig.Rank = 7;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		while(1);
	}

	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = 8;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		while(1);
	}
}

void ADC1_Gpio_Init() {
	GPIO_InitTypeDef GPIO_InitStruct;

	/**ADC1 GPIO Configuration
	 PC0     ------> ADC1_IN10
	 PC2     ------> ADC1_IN12
	 PA0-WKUP     ------> ADC1_IN0
	 PA2     ------> ADC1_IN2
	 PA4     ------> ADC1_IN4
	 PA6     ------> ADC1_IN6
	 PC4     ------> ADC1_IN14
	 PB1     ------> ADC1_IN9
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void ADC1_DMA_Init() {
	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE()
	;

	/* DMA interrupt init */
	/* DMA1_Channel1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

	/* Peripheral DMA init*/

	hdma_adc1.Instance = DMA1_Channel1;
	hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
	hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	hdma_adc1.Init.Mode = DMA_CIRCULAR;
	hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
	if (HAL_DMA_Init(&hdma_adc1) != HAL_OK) {
		while(1);
	}

	__HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);
}

void ADC1_Init()
{
	ADC1_Gpio_Init();
	ADC1_Periph_Init();
	ADC1_DMA_Init();
	HAL_ADC_Start_DMA(&hadc1, &sample[0], 8);
}

void ADC1_pause()
{
	HAL_ADC_Stop_DMA(&hadc1);
}

void ADC1_resume()
{
	HAL_ADC_Start_DMA(&hadc1, &sample[0], 8);
}

void DMA1_Channel1_IRQHandler(void) {
	static uint16_t counter = 0;
	static uint32_t sum[8] = {0,0,0,0,0,0,0,0};
	static peak_detector_t gp2y_peak_detector;
	HAL_DMA_IRQHandler(&hdma_adc1);

	uint32_t gp2y_channel_value = sample[2];
	if(gp2y_should_reset)
	{
		peak_detector_reset(&gp2y_peak_detector);
		gp2y_should_reset = 0;
	}
	peak_detector_new_sample(&gp2y_peak_detector, gp2y_channel_value);

	//average from ADC_AVERAGE_SIZE samples
	if (counter < ADC_AVERAGE_SIZE) {
		for (int i = 0; i < 8; i++) {
			sum[i] += sample[i];
		}
		counter++;
	} else {
		counter = 0;
		for(int i = 0; i<8; i++)
		{
			adc_value[i] = sum[i]/ADC_AVERAGE_SIZE;
			sum[i] = 0;
		}
		flaga = 1;
	}
	adc_value[2] = peak_detector_get(&gp2y_peak_detector);
}
