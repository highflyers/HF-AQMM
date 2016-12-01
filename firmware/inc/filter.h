#ifndef FILTER_H_
#define FILTER_H_

typedef struct {
	uint32_t *coeffs_a;
	uint32_t coeffs_a_size;
	uint32_t *coeffs_b;
	uint32_t coeffs_b_size;
	uint32_t *input_history;
	uint32_t input_history_size;
	uint32_t *output_history;
	uint32_t output_history_size;
} filter_t;

uint32_t filter_new_data(filter_t *filter, uint32_t value);
uint32_t filter_get_output(filter_t *filter);
void filter_reset(filter_t *filter, uint32_t value);

#endif /* FILTER_H_ */
