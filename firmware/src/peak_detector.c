#include <peak_detector.h>

void peak_detector_new_sample(peak_detector_t *detector, int sample)
{
	detector->maxValue = sample > detector->maxValue ? sample : detector->maxValue;
}

int peak_detector_get(peak_detector_t *detector)
{
	return detector->maxValue;
}

void peak_detector_reset(peak_detector_t *detector)
{
	detector->maxValue = DETECTOR_MIN_VALUE;
}
