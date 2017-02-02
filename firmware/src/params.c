#include "params.h"

#include <stdio.h>
#include <string.h>

int params_command(parameters_t * params, char * str)
{
	int index = 0;
	int address = 0;
	int value = 0;
	while (params__is_white_char(str[index]))
	{
		++index;
	}
	if (params__is_data_char(str[index]))
	{
		index += params__get_first_int(str+index, &address);
	}
	else
	{
		return -1;
	}
	while (params__is_white_char(str[index]))
	{
		++index;
	}
	if (params__is_address_ending_char(str[index]))
	{
		++index;
	}
	else
	{
		return -1;
	}
	while (params__is_white_char(str[index]))
	{
		++index;
	}
	if (params__is_data_char(str[index]))
	{
		index += params__get_first_int(str + index, &value);
		if (address < params->size)
		{
			params->array[address] = value;
		}
		return index;
	}
	else if (param__is_list_opening_char(str[index]))
	{
		while (!params__is_address_ending_char(str[index]))
		{
			++index;
			while (params__is_white_char(str[index]) || params__is_list_delim_char(str[index]))
			{
				++index;
			}
			index += params__get_first_int(str + index, &value);
			if (address < params->size)
			{
				params->array[address] = value;
				++address;
			}
		}
	}
	return index;
}

void params_sprint(parameters_t *params, char *str, size_t max_size)
{
	size_t bytes_written = 0;
	for (size_t i = 0; i < params->size; ++i)
	{
		bytes_written += snprintf(str + bytes_written, max_size - bytes_written, "%d = %d\n", i, params->array[i]);
	}
}

int params__get_first_int(char *str, int *dest)
{
	int index = 0;
	int string_length = strlen(str);
	int data_length = 0;
	int value = 0;
	int sign_value = 1;
	int sign_present = params__is_sign_char(str[0]);
	if (sign_present)
	{
		sign_value = params__sign_value(str[0]);
		++index;
	}
	if (params__is_data_char(str[index]))
	{
		while (params__is_data_char(str[index]))
		{
			++index;
		}
		data_length = index;
		--index;
		for (; index >= 0; --index)
		{
			int char_value = params__char_value(str[index]);
			int tenths_place = params__ten_power(data_length - index - 1);
			value += char_value * tenths_place;
		}
	}
	value *= sign_value;
	(*dest) = value;
	return data_length;
}

int params__ten_power(int power)
{
	int value = 1;
	for (int i = 0; i < power; ++i)
	{
		value *= 10;
	}
	return value;
}

int params__char_value(char c)
{
	int value = 0;
	if (c >= '0' && c <= '9')
	{
		value = (int)(c - '0');
	}
	return value;
}

int params__is_data_char(char c)
{
	int ret = 0;
	ret |= (c >= '0' && c <= '9');
	ret |= params__is_sign_char(c);
	return ret;
}

int params__is_sign_char(char c)
{
	int ret = 0;
	ret |= (c == '+' || c == '-');
	return ret;
}

int params__sign_value(char c)
{
	if (c == '+')
	{
		return 1;
	}
	else if (c == '-')
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int params__is_white_char(char c)
{
	int ret = 0;
	ret |= (c == ' ');
	ret |= (c == '\t');
	return ret;
}

int params__is_address_ending_char(char c)
{
	return (c == ':');
}

int param__is_list_opening_char(char c)
{
	return (c == '[');
}

int param__is_list_closing_char(char c)
{
	return (c == ']');
}

int params__is_list_delim_char(char c)
{
	return (c == ',');
}
