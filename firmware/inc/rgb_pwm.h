/*
 * rgb_pwm.h
 *
 *  Created on: 26 lis 2016
 *      Author: Karollo
 */

#ifndef RGB_PWM_H_
#define RGB_PWM_H_

#include "stm32f1xx.h"

#define PWM_PERIOD 9999

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

typedef enum{
	LED_B = 0,
	LED_R = 1,
	LED_G = 2
}LED_TypeDef;

void RGB_Pwm_Gpio_Init();
void RGB_Timer3_Init();
void RGB_Timer4_Init();
void RGB_Pwm_Init();
void RGB_Set_PulseWidth(LED_TypeDef led, uint8_t pulseWidth);

#endif /* RGB_PWM_H_ */
