/*
 * board.h
 *
 *  Created on: 24.11.2016
 *      Author: macie
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <stm32f1xx.h>
#include <stm32f1xx_hal_usart.h>

/*
 * 	Platform:	STM32F100RBT6B
 *  Medium density value line
 *	Flash size:	128k
 *
 *	MQ131_OUT		PA0-WKUP	ADC1_IN0
 *	MQ131_EN		PB12		TIM1_BKIN
 *
 *	TGS1_OUT		PC0			ADC1_IN10
 *	TGS1_EN			PB8			TIM4_CH3 / TIM16_CH1
 *
 *	TGS2_OUT		PA2			ADC1_IN2
 *	TGS2_EN			PB14		TIM1_CH2N
 *
 *	GP2Y_OUT		PA4			ADC1_IN4
 *	GP2Y_EN			PB0			ADC1_IN8 / TIM3_CH3
 *
 *	NAP500_OUT		PC4			ADC1_IN14
 *
 *	TGS5042_OUT		PA6			ADC1_IN6
 *
 *	TGS5342_OUT		PC2			ADC1_IN12
 *
 *	DHT22_OUT		PB15
 *
 *	FT_RX			PA9			USART1_TX
 *	FT_TX			PA10		USART1_RX
 *
 *	I2C1_SCL		PB8
 *	I2C1_SDA		PB9
 *
 *	LIPO_IN			PB1			ADC1_IN9/TIM3_CH4
 *	LIPO_IN_EN		PA11		USART1_CTS / TIM1_CH4
 *
 *	BUZZER			PC10
 *	BUTTON1			PA12		USART1_RTS / TIM1_ETR
 *
 *	TMS				PA13		JTMS/SWDIO
 *	TCLK			PA14		JTCK/SWCLK
 *	TDI				PA15		JTDI
 *	TDO				PB3			JTDO
 *	NJRESET			PB4			NJRST
 *
 *	LED_B			PB5			I2C1_SMBA / TIM16_BKIN || TIM3_CH2 / SPI1_MOSI
 *	LED_R			PB6			TIM4_CH1
 *	LED_G			PB7			TIM17_CH1N / TIM4_CH2
 *
 *	PX_RX			PB10		USART3_TX
 *	PX_TX			PB11		USART3_RX
*/

#define BUTTON1_GPIO					GPIOA
#define BUTTON1_PIN						GPIO_PIN_12
#define BUTTON1_GPIO_RCC_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()

#define LED_B_GPIO      				GPIOB
#define LED_B_PIN 						GPIO_PIN_5
#define LED_R_GPIO						GPIOB
#define LED_R_PIN						GPIO_PIN_6
#define LED_G_GPIO      				GPIOB
#define LED_G_PIN						GPIO_PIN_7
#define LED_GPIO_RCC_ENABLE() 			__HAL_RCC_GPIOB_CLK_ENABLE()

#define UART_USB_REG					USART1
#define UART_USB_RCC_ENABLE()			__HAL_RCC_USART1_CLK_ENABLE()
#define UART_USB_RX_GPIO				GPIOA
#define UART_USB_RX_PIN					GPIO_PIN_10
#define UART_USB_RX_GPIO_RCC_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()
#define UART_USB_TX_GPIO				GPIOA
#define UART_USB_TX_PIN					GPIO_PIN_9
#define UART_USB_TX_GPIO_RCC_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()

#define I2C1_REG						I2C1
#define I2C1_CLK_ENABLE()				__HAL_RCC_I2C1_CLK_ENABLE()
#define I2C1_CLK_DISABLE()				__HAL_RCC_I2C1_CLK_DISABLE()
#define I2C1_SCL_GPIO_REG				GPIOB
#define I2C1_SCL_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C1_SCL_GPIO_PIN				GPIO_PIN_8
#define I2C1_SDA_GPIO_REG				GPIOB
#define I2C1_SDA_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C1_SDA_GPIO_PIN				GPIO_PIN_9

#endif /* BOARD_H_ */
