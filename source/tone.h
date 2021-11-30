#ifndef _TONE_H_
#define _TONE_H_

#include <stdint.h>
#include "adc.h"

extern int frequencies[4];
extern int next_tone;
extern int samples;
extern uint16_t op_buffer[ADC_BUFFER_SIZE], ip_buffer[ADC_BUFFER_SIZE];

enum {
	A4 = 440,
	D5 = 587,
	E5 = 659,
	A5 = 880
};

size_t tone_to_samples(int input_freq, uint16_t *buffer, size_t size);

#endif
