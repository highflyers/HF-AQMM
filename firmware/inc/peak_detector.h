#ifndef PEAK_DETECTOR_H_
#define PEAK_DETECTOR_H_

#define DETECTOR_MIN_VALUE	-10000

typedef struct
{
	int maxValue;
} peak_detector_t;

void peak_detector_new_sample(peak_detector_t *detector, int sample);
int peak_detector_get(peak_detector_t *detector);
void peak_detector_reset(peak_detector_t *detector);

#endif /* PEAK_DETECTOR_H_ */
