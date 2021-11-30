/*
 * PES Assignment 7
 *
 * File Name: dac.h
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */

#ifndef _DAC_H_
#define _DAC_H_

/*	LIBRARY FILES	*/
#include "MKL25Z4.h"
#include "stdio.h"
#include "stdint.h"

/*	MACROS	*/
#define SAMPLING_FREQUENCY			48000
#define SYS_CLOCK					48e6

/*	GLOBAL VARIABLES	*/
extern uint16_t buffer[1024]; 	//declared here, initialized in dac.c
extern uint32_t count;			//declared here, initialized in dac.c

/*	FUNCTION PROTOTYPES	*/
/* -----------------------------------------------------------------
 * @brief		: 	Initialize the DAC to generate the analog sine wave
 *
 * @parameters	: 	none
 *
 * @returns		: 	none
 --------------------------------------------------------------------*/
void Init_DAC();

/*	FUNCTION PROTOTYPES	*/
/* -----------------------------------------------------------------
 * @brief		: 	Begin the DAC to generate analog wave
 *
 * @parameters	: 	frequency:	an array in which the values of the
 * 					samples of the frequency to be generated are stored
 *
 * 					cnt: number of bytes to be converted into analog wave
 *
 * @returns		: 	none
 --------------------------------------------------------------------*/
void DAC_begin(uint16_t *frequency, uint32_t cnt);

#endif /*_DAC_H_*/
