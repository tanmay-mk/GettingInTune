/*
 * PES Assignment 7
 *
 * File Name: dma.c
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */
/*	LIBRARY FILES	*/
#include "fsl_debug_console.h"

/*	OTHER FILES TO BE INCLUDED	*/
#include "dma.h"
#include "dac.h"
#include "tone.h"

/*	GLOBAL VARIABLES	*/
int dma_rollover = 0;	//to count number of cycles of a sine wave transferred by DMA
int tone_index=0;		//declared in dma.h, initialized here
bool flag = false;		//declared in dma.h, initialized here

/*
 * @brief:see documentation in dma.h
 */
void Init_DMA()
{
	//  Gate Clock
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	// Disabbling for Configuration
	DMAMUX0->CHCFG[0] = 0;

	// interrupt once done, increment src, src size: 16 bits, dest size: 16 bits, enable requests, enable DMA0
	DMA0->DMA[0].DCR = DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) | DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK;

	// NVIC Config
	NVIC_SetPriority(DMA0_IRQn, 2);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	// Enable DMA MUX channel with TPM0 overflow as trigger
	DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_SOURCE(54);
}

/* -----------------------------------------------------------------
 * @brief		: 	Interrupt service routine of DMA
 *
 * @parameters	: 	none
 *
 * @returns		: 	none
 --------------------------------------------------------------------*/
void DMA0_IRQHandler(void)
{
	//Clear done flag in IRQ
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;

	dma_rollover++;
	/*
	 * @brief:
	 * Somehow, in this implementation of DMA and the entire assignment,
	 * time period (time to change to next wave) of each wave is coming
	 * out to be different.
	 *
	 * for A4 (440 Hz), the period is 8 sec
	 * for D5 (587 Hz), the period is 12 sec
	 * for E5 (659 Hz), the period is 14 sec
	 * for A5 (880 Hz), the period is 18 sec
	 *
	 * thus, in order to correctly fit the period to 1 sec, the comparisons
	 * have been downscaled with respective values.
	 *
	 */
	switch(frequencies[tone_index])
	{
	case A4:
		if (dma_rollover == A4/8)
		{
			flag = true; //set the flag to true
			tone_index++;
			dma_rollover=0;
		}
		break;
	case D5:
		if (dma_rollover == D5/12)
		{
			flag = true;
			tone_index++;
			dma_rollover=0;
		}
		break;

	case E5:
		if (dma_rollover == E5/14)
		{
			flag = true;
			tone_index++;
			dma_rollover=0;
		}
		break;
	case A5:
		if (dma_rollover == A5/18)
		{
			flag = true;
			tone_index=0;
			dma_rollover=0;
		}
		break;

	default:
		break;
	}

	// DMA playback
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) buffer);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));

	// Bytes to transfer
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(count * 2);
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}
