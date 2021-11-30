/*
 * PES Assignment 7
 *
 * File Name: main.c
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */

/*	LIBRARY FILES	*/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/*	OTHER FILES TO BE INCLUDED	*/
#include "autocorrelate.h"
#include "stdint.h"
#include "tone.h"
#include "dma.h"
#include "tpm.h"
#include "adc.h"
#include "dac.h"
#include "sinx.h"
#include "test_sinx.h"

/*	GLOBAL VARIABLES	*/
//variable declared in tone.c, initialized here.
int next_tone = 0;

/*
 * @brief   Application entry point.
 */
int main(void)
{
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
		/* Init FSL debug console. */
		BOARD_InitDebugConsole();
	#endif

	//initializing peripherals
	Init_DAC();
    Init_DMA();
    TPM0_Init();
    TPM1_Init(ADC_SAMPLING_FREQUENCY);
    ADC_Init();
    calibrate_ADC();
    ADC_Init();

    PRINTF("Testing Sine function.\r\n");
    test_sine();
    PRINTF("\r\nSine error calculated! Starting sine waves.\r\n\n");

    /*
     * @brief: Starting first sine wave of frequency 440 (A4) here to initiate DMA,
     * 			ADC and DAC transfers. All other computations of samples and buffers
     * 			is done in generate_next_tone() in tone.c
     */
	PRINTF("Frequency: %d Hz\r\n", frequencies[next_tone]);
	//calculating samples for A4 tone
	samples = tone_to_samples(frequencies[next_tone], op_buffer, ADC_BUFFER_SIZE);
	DAC_begin(op_buffer, samples);
	ADC_Buffer(ip_buffer, ADC_BUFFER_SIZE);
	analysis(ip_buffer, ADC_BUFFER_SIZE);
	next_tone++;

    while(1)
    {
    	//function which calculates the samples of next
    	//tone to be played and waits until the first
    	//tone has been played
    	generate_next_tone();

    } //while

} //main
