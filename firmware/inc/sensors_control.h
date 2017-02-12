#ifndef SENSORS_CONTROL_H_
#define SENSORS_CONTROL_H_

#include <board.h>

#define SENSOR_MQ131						0
#define SENSOR_TGS1							1
#define SENSOR_TGS2							2
#define SENSOR_CONTROL_NUMBER_OF_SENSORS	3

void sensors_control_init();
void sensors_control_enable(int sensor);
void sensors_control_disable(int sensor);
void sensors_control_enable_all();
void sensors_control_disable_all();
GPIO_TypeDef *sensors_control_gpio(int sensor);
uint16_t sensors_control_pin(int sensor);

#endif /* SENSORS_CONTROL_H_ */
