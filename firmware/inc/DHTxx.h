#ifndef DHTXX_H_
#define DHTXX_H_

#include <board.h>
#include <stm32f1xx_hal_gpio.h>

#define DHTxx_START_LENGTH			1000
#define DHTxx_TIMEOUT				100000
#define DHTxx_THRESHOLD				20

#define DHTxx_ERROR_OK				0
#define DHTxx_ERROR_CHECKSUM		1
#define DHTxx_ERROR_TIMEOUT			2

void DHTxx_init();
int DHTxx_read(int *T, int *RH);
void DHTxx_start();
uint8_t DHTxx_read_byte();
uint32_t DHTxx_wait_for_ready();
uint32_t DHTxx_read_bit();
uint32_t DHTxx_read_signal_length();
void DHTxx_up();
void DHTxx_down();
uint32_t DHTxx_wait_for_low();
uint32_t DHTxx_wait_for_high();
void DHTxx_sleep(int delay);

#endif /* DHTXX_H_ */
