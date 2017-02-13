#include <uart_px.h>

UART_HandleTypeDef uart_PX_handle;
int uart_px_input_flag;
char uart_px_input_char;

void uart_px_gpio_init()
{
	GPIO_InitTypeDef g;

	//	RX pin
	UART_PX_RX_GPIO_RCC_ENABLE();
	g.Mode = GPIO_MODE_AF_INPUT;
	g.Pin = UART_PX_RX_PIN;
	g.Speed = GPIO_SPEED_HIGH;
	g.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(UART_PX_RX_GPIO, &g);

	//	TX pin
	UART_PX_TX_GPIO_RCC_ENABLE();
	g.Mode = GPIO_MODE_AF_PP;
	g.Pin = UART_PX_TX_PIN;
	g.Speed = GPIO_SPEED_HIGH;
	g.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(UART_PX_TX_GPIO, &g);
}

void uart_px_periph_init()
{
	UART_PX_RCC_ENABLE();
	uart_PX_handle.Instance = UART_PX_REG;
	uart_PX_handle.State = HAL_UART_STATE_RESET;
	uart_PX_handle.Init.BaudRate = UART_PX_BAUD;
	uart_PX_handle.Init.Mode = USART_MODE_TX_RX;
	uart_PX_handle.Init.Parity = USART_PARITY_NONE;
	uart_PX_handle.Init.StopBits = USART_STOPBITS_1;
	uart_PX_handle.Init.WordLength = USART_WORDLENGTH_8B;
	HAL_UART_Init(&uart_PX_handle);
	uart_PX_handle.State = HAL_UART_STATE_READY;

	HAL_NVIC_SetPriority(UART_PX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(UART_PX_IRQn);
}

void uart_px_init()
{
	uart_px_gpio_init();
	uart_px_periph_init();
	uart_px_start_reception();
}

void uart_px_send(char *data, uint16_t size)
{
	while (HAL_UART_Transmit(&uart_PX_handle, (uint8_t*) data, size, HAL_MAX_DELAY)
			!= HAL_OK);
}

void uart_px_send_it(char *data, uint16_t size)
{
	while (HAL_UART_Transmit_IT(&uart_PX_handle, (uint8_t*) data, size)
			!= HAL_OK);
}

void uart_px_start_reception()
{
	HAL_UART_Receive_IT(&uart_PX_handle, (uint8_t*) (&uart_px_input_char), 1);
}

void uart_px_receive_callback()
{
	uart_px_input_flag = 1;
}

void USART3_IRQHandler()
{
	HAL_UART_IRQHandler(&uart_PX_handle);
}
