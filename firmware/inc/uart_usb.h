#ifndef UART_USB_H_
#define UART_USB_H_

#include <board.h>

#define UART_USB_INPUT_BUFFER_SIZE		1024

extern UART_HandleTypeDef uart_usb_handle;
extern int uart_input_flag;
extern char uart_input_buffer[UART_USB_INPUT_BUFFER_SIZE];

#define UART_USB_BAUD		9600

void uart_usb_gpio_init();
void uart_usb_periph_init();
void uart_usb_init();
void uart_usb_start_reception();
void uart_usb_send(char *data, uint16_t size);
int uart_usb_is_newline_char(char c);

#endif /* UART_USB_H_ */
