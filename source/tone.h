/*
 * PES Assignment 7
 *
 * File Name: tone.h
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */

#ifndef _TONE_H_
#define _TONE_H_

/* 	LIBRARY FILES	*/
#include <stdint.h>

/* 	OTHER FILES TO BE INCLUDED	*/
#include "adc.h"

/* 	MACROS	*/
#define TOTAL_NUMBER_OF_TONES		4

/* 	GLOBAL VARIABLES	*/
extern int frequencies[TOTAL_NUMBER_OF_TONES]; 	//declared here, initialized in tone.c
extern int next_tone;							//declared here, initialized in main.c
extern int samples;								//declared here, initialized in main.c

//declared here, initialized in main.c
extern uint16_t op_buffer[ADC_BUFFER_SIZE], ip_buffer[ADC_BUFFER_SIZE];

/* 	ENUMERATION OF FREQUENCIES FOR BETTER READABILITY	*/
enum {
	A4 = 440,
	D5 = 587,
	E5 = 659,
	A5 = 880
};

/* 	FUNCTION PROTOTYPES	*/
/* -----------------------------------------------------------------
 * @brief		: 	Generates samples of the next tone to be played
 *
 * @parameters	: 	none
 *
 * @returns		: 	none
 --------------------------------------------------------------------*/
void generate_next_tone();

/* -----------------------------------------------------------------
 * @brief		: 	Generates samples of the tone and stores it in a buffer
 *
 * @parameters	: 	buffer		:	the buffer in which the samples are to be stored
 * 					input_freq	:	frequency to be sampled
 * 					size		:	maximum number of bytes that can be sampled
 *
 * @returns		: 	total number of samples created and stored in buffer
 --------------------------------------------------------------------*/
size_t tone_to_samples(int input_freq, uint16_t *buffer, size_t size);

#endif
