#ifndef UART_PX_H_
#define UART_PX_H_

#include <board.h>

#define UART_PX_BAUD		57600

extern UART_HandleTypeDef uart_PX_handle;
extern int uart_px_input_flag;

void uart_px_gpio_init();
void uart_px_periph_init();
void uart_px_init();
void uart_px_start_reception();
void uart_px_send(char *data, uint16_t size);
void uart_px_send_it(char *data, uint16_t size);
void uart_px_receive_callback();

#endif /* UART_PX_H_ */
