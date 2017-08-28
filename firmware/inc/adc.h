/*
 * adc.h
 *
 *  Created on: 1 gru 2016
 *      Author: Karollo
 */

#ifndef ADC_H_
#define ADC_H_

#define ADC_AVERAGE_SIZE		5000

void ADC1_Init();
void ADC1_Periph_Init();
void ADC1_Gpio_Init();
void ADC1_DMA_Init();
void ADC1_pause();
void ADC1_resume();

#endif /* ADC_H_ */
