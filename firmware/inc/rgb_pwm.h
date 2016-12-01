/*
 * rgb_pwm.h
 *
 *  Created on: 26 lis 2016
 *      Author: Karollo
 */

#ifndef RGB_PWM_H_
#define RGB_PWM_H_

#include "stm32f1xx.h"

#define PWM_PERIOD 				9999
#define RGB_PATTERN_MIN			5
#define RGB_PATTERN_DELTA		10
#define RGB_PATTERN_MAX			250

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
void RGB_Set_Color(uint8_t R, uint8_t G, uint8_t B);
void RGB_Set_Pattern_Color(uint8_t R, uint8_t G, uint8_t B);
void RGB_Pattern_Update();

#endif /* RGB_PWM_H_ */
