/*
 * PES Assignment 7
 *
 * File Name: dma.h
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */
#ifndef _DMA_H_
#define _DMA_H_

/*	LIBRARY FILES	*/
#include "MKL25Z4.h"
#include <stdbool.h>

/*	GLOBAL VARIABLES	*/
extern int tone_index;		//declared here, initialized in dma.c
extern bool flag;			//declared here, initialized in dma.c

/*	FUNCTION PROTOTYPES	*/
/* -----------------------------------------------------------------
 * @brief		: 	Initialize the DMA to to transfer bytes to the DAC
 *
 * @parameters	: 	none
 *
 * @returns		: 	none
 --------------------------------------------------------------------*/
void Init_DMA();

#endif /*_DMA_H_*/
