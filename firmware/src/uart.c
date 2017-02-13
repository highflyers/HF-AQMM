#include <uart_px.h>
#include <uart_usb.h>

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &uart_PX_handle)
	{
		uart_px_receive_callback();
	}
	else if(huart == &uart_usb_handle)
	{
		uart_usb_receive_callback();
	}
}
