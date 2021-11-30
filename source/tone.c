#include "tone.h"
#include "dac.h"
#include "sinx.h"
#include "fsl_debug_console.h"
#include "autocorrelate.h"
#include "dma.h"


int frequencies[4] = {A4, D5, E5, A5};
int samples;
uint16_t op_buffer[ADC_BUFFER_SIZE], ip_buffer[ADC_BUFFER_SIZE];

size_t tone_to_samples(int input_freq, uint16_t *buffer, size_t size) {

	int32_t temp;
	int i=0;
	int cycles = size / ((SAMPLING_FREQUENCY + (input_freq/2)) / input_freq);
	int samples = ((SAMPLING_FREQUENCY + (input_freq/2)) / input_freq) * cycles;

	for (i=0; i < samples; i++) {
		// Needs to be converted appropriately
		temp = fp_sin(i * TWO_PI / ((SAMPLING_FREQUENCY + (input_freq/2)) / input_freq) ) + TRIG_SCALE_FACTOR;
		buffer[i] = temp;
	}

	PRINTF("Generated %d samples at %d Hz; computed period=%d, observed=%d\r\n",
			samples, input_freq, ((SAMPLING_FREQUENCY + (input_freq/2)) / input_freq),
	  autocorrelate_detect_period(buffer, samples, 0));

   return samples;
}

void generate_next_tone()
{
	PRINTF("Frequency: %d Hz\r\n", frequencies[next_tone]);
	samples = tone_to_samples(frequencies[next_tone], op_buffer, ADC_BUFFER_SIZE);
	while (!flag)
		;
	flag = false;
	next_tone++;
	DAC_begin(op_buffer, samples);
	ADC_Buffer(ip_buffer, ADC_BUFFER_SIZE);
	analysis(ip_buffer, ADC_BUFFER_SIZE);
	if(next_tone==4)
	{
		next_tone = 0;
	}
}
