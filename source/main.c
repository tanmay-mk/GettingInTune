
#include <adc.h>
#include <dac.h>
#include <sinx.h>
#include <stdio.h>
#include <test_sinx.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "autocorrelate.h"
#include "stdint.h"
#include "tone.h"
#include "dma.h"
#include "tpm.h"
#include "adc.h"

int next_tone = 0;
/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    int samples, i=0;
    uint16_t op_buffer[ADC_BUFFER_SIZE], ip_buffer[ADC_BUFFER_SIZE];
    DAC_Init_();
    DMA_Init_();
    TPM0_Init_();
    TPM1_Init_(ADC_SAMPLING_FREQUENCY);
    ADC_Init_();

    PRINTF("Testing Sine function.\r\n");
    test_sine();
    PRINTF("\r\n Sine error calculated! Starting sine waves.\r\n\n");

	PRINTF("Frequency: %d Hz\r\n", frequencies[next_tone]);
	samples = tone_to_samples(frequencies[i], op_buffer, ADC_BUFFER_SIZE);
	DAC_begin(op_buffer, samples);
	ADC_Buffer(ip_buffer, ADC_BUFFER_SIZE);
	analysis(ip_buffer, ADC_BUFFER_SIZE);
	next_tone++;

    while(1)
    {
    	generate_next_tone();
    }

    // Infinite Loop to Run through the frequencies
    for(i = 0; i<=4; i++) {
    	if(i==4) {
			i=0;
		}
    	PRINTF("Frequency: %d Hz\r\n", frequencies[i]);
    	samples = tone_to_samples(frequencies[i], op_buffer, ADC_BUFFER_SIZE);
    	while (!flag)
    		;
    	flag = false;
    	DAC_begin(op_buffer, samples);
    	ADC_Buffer(ip_buffer, ADC_BUFFER_SIZE);
    	analysis(ip_buffer, ADC_BUFFER_SIZE);
    }
    return 0 ;
}
