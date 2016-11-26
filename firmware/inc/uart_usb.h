#ifndef UART_USB_H_
#define UART_USB_H_

#include <board.h>

extern UART_HandleTypeDef uart_usb_handle;

#define UART_USB_BAUD		9600

void uart_usb_gpio_init();
void uart_usb_periph_init();
void uart_usb_init();

void uart_usb_send(char *data, uint16_t size);

#endif /* UART_USB_H_ */
