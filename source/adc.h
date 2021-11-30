/*
 * PES Assignment 7
 *
 * File Name: adc.h
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */
#ifndef _ADC_H_
#define _ADC_H_

/*	LIBRARY FILES	*/
#include <stdint.h>

/*	MACROS	*/
#define SYS_CLOCK					48e6
#define ADC_SAMPLING_FREQUENCY 		96000
#define ADC_BUFFER_SIZE 			1024

/*	FUNCTION PROTOTYPES	*/
/* -----------------------------------------------------------------
 * @brief		: 	Initialize the ADC0 for analysis of the Analog
 * 					signal generated
 *
 * @parameters	: 	none
 *
 * @returns		: 	none
 --------------------------------------------------------------------*/
void ADC_Init();


/* -----------------------------------------------------------------
 * @brief		: 	Wait for the ADC transfer to be completed and the
 * 					copy the values in the buffer
 *
 * @parameters	: 	buffer	:	the buffer in which the ADC values will be stored
 * 					count	: 	number of bytes to be copied in the buffer
 *
 * @returns		: 	none
  -----------------------------------------------------------------*/
void ADC_Buffer(uint16_t *buffer, uint32_t count);


/* -----------------------------------------------------------------
 * @brief		: 	analyzes the buffer which has stored the ADC values and computes
 * 					the frequency and other parameters to help debug the accuracy of
 * 					the analog signal generated
 *
 * @parameters	: 	buffer	:	the buffer in which the ADC values will be stored
 * 					count	: 	number of bytes in the buffer
 *
 * @returns		: 	none
  -----------------------------------------------------------------*/
void analysis(uint16_t *buffer, uint32_t count);


#endif /*_ADC_H_*/
