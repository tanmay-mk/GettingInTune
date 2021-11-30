/*
 * PES Assignment 7
 *
 * File Name: tpm.h
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */

#ifndef _TPM_H_
#define _TPM_H_

/*	LIBRARY FILES	*/
#include "MKL25Z4.h"

/*	MACROS	*/
#define SYS_CLOCK		48e6
#define BEGIN_TPM1 		TPM1->SC |= TPM_SC_CMOD(1);
#define STOP_TPM1  		TPM1->SC &= ~TPM_SC_CMOD_MASK;

/* 	FUNCTION PROTOTYPES	*/
/* -----------------------------------------------------------------
 * @brief		: 	Initializes TPM0 for DMA transfers
 *
 * @parameters	: 	none
 *
 * @returns		: 	none
 --------------------------------------------------------------------*/
void TPM0_Init();

/* -----------------------------------------------------------------
 * @brief		: 	Initializes TPM1 for ADC transfers
 *
 * @parameters	: 	samples	:	used to calculate top value
 *
 * @returns		: 	none
 --------------------------------------------------------------------*/
void TPM1_Init(int sample);

#endif /*_TPM_H_*/
