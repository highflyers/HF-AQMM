#include "stm32f1xx_hal.h"	// TODO: find better source for uint* typedefs
#include "filter.h"

/*
 * TODO:
 * This filter implementation assumes IIR filter with only one coefficient of each type.
 */
uint32_t filter_new_data(filter_t *filter, uint32_t value)
{
	uint32_t new_value = 0;
	new_value = filter->coeffs_a[0] * value + filter->coeffs_b[0] * filter->output_history[0];
	new_value /= (filter->coeffs_a[0] + filter->coeffs_b[0]);
	filter->output_history[0] = new_value;
	return new_value;
}

uint32_t filter_get_output(filter_t *filter)
{
	return filter->output_history[0];
}

void filter_reset(filter_t *filter, uint32_t value)
{
	for(size_t i = 0; i < filter->output_history_size; ++i)
	{
		filter->output_history[i] = value;
	}
	for(size_t i = 0; i < filter->input_history_size; ++i)
	{
		filter->input_history[i] = value;
	}
}
