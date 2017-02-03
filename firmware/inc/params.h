#pragma once

#include <stddef.h>

typedef struct
{
	int *array;
	size_t size;
} parameters_t;

int params_command(parameters_t *params, char * str);

void params_sprint(parameters_t * params, char * str, size_t max_size);

void params_print(parameters_t * params);

int params__get_first_int(char * str, int * dest);

int params__ten_power(int power);

int params__char_value(char c);

int params__is_data_char(char c);

int params__is_sign_char(char c);

int params__sign_value(char c);

int params__is_white_char(char c);

int params__is_address_ending_char(char c);

int param__is_list_opening_char(char c);

int param__is_list_closing_char(char c);

int params__is_list_delim_char(char c);
