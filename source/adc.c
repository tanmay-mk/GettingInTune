

#include "adc.h"
#include "MKL25Z4.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "fsl_debug_console.h"
#include "autocorrelate.h"


void ADC_Init_() {
	// Gating
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	// normal power mode, no clock divide, long sampling enabled, 16-bit conversion (single-ended), use bus clock
	ADC0->CFG1 = ADC_CFG1_ADLPC(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_ADLSMP(0) | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0);

	// Set the ADC0 configuration 2 register
	ADC0->CFG2 = 0;

	// DMA initially disabled
	ADC0->SC2 = ADC_SC2_ADTRG(1) | ADC_SC2_ACFE(0) | ADC_SC2_DMAEN(0) | ADC_SC2_REFSEL(0);

	// Input Channel for DAC is the input for ADC
	ADC0->SC1[0] = ADC_SC1_AIEN(0) | ADC_SC1_DIFF(0) | ADC_SC1_ADCH(23);

	// Enable ADC0 triggering from TPM1 overflow
	SIM->SOPT7 = SIM_SOPT7_ADC0ALTTRGEN(1) | SIM_SOPT7_ADC0TRGSEL(9);

}

void ADC_Buffer(uint16_t *buffer, uint32_t sample_count) {

	int i =0;
	// Begin TPM
	BEGIN_TPM1

	for (i =0; i < sample_count; i++) {
		while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		      ;

		buffer[i] = ADC0->R[0];
	}

	// Stop Sampling
	STOP_TPM1
}

void analysis(uint16_t *buffer, uint32_t count) {

	int i=0;
	uint32_t max, sum = 0;
	int min;

	min = buffer[0];
	max = buffer[0];


	// Keeps to within limit
	for (i=0; i < count; i++) {
		if (buffer[i] > max) {
			max = buffer[i];
		}
		if (buffer[i] < min) {
			min = buffer[i];
		}

		sum+= buffer[i];

	}

	int period = autocorrelate_detect_period(buffer, count, 1);
	int frequency = ADC_SAMPLING_FREQUENCY / period;
	PRINTF("min=%u max=%u avg=%u period=%d frequency=%d Hz\r\n\n",
	      min, max, sum / count, period, frequency);

}

