#ifndef BUTTON_H_
#define BUTTON_H_

#include <filter.h>

extern volatile int button_flip_flop_status;

void button_init();
void button_callback();

#endif /* BUTTON_H_ */
