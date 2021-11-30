#include "dma.h"
#include "dac.h"
#include "fsl_debug_console.h"
#include "tone.h"


int dma_rollover = 0;
int tone_index=0;
bool flag = false;

void DMA_Init_() {

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

/*
 * IRQ Handler
 */
void DMA0_IRQHandler(void)
{
	// Goddamit, have to Clear done flag in IRQ
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;

	dma_rollover++;

	switch(frequencies[tone_index])
	{
	case A4:
		if (dma_rollover == A4/8)
		{
			//PRINTF("DMA ROLLOVER : %d\n\r", dma_rollover);
			flag = true;
			tone_index++;
			dma_rollover=0;
			if (tone_index == 4)
			{
				tone_index=0;
			}
		}
		break;
	case D5:
		if (dma_rollover == D5/11)
		{
			//PRINTF("DMA ROLLOVER : %d\n\r", dma_rollover);
			flag = true;
			tone_index++;
			dma_rollover=0;
			if (tone_index == 4)
			{
				tone_index=0;
			}
		}
		break;

	case E5:
		if (dma_rollover == E5/13)
		{
			//PRINTF("DMA ROLLOVER : %d\n\r", dma_rollover);
			flag = true;
			tone_index++;
			dma_rollover=0;
			if (tone_index == 4)
			{
				tone_index=0;
			}
		}
		break;
	case A5:
		if (dma_rollover == A5/16)
		{
			//PRINTF("DMA ROLLOVER : %d\n\r", dma_rollover);
			flag = true;
			tone_index++;
			dma_rollover=0;
			if (tone_index == 4)
			{
				tone_index=0;
			}
		}
		break;

	}
	//PRINTF("DMA ROLLOVER : %d\n\r", dma_rollover);


	// DMA playback
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) buffer);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));

	// Bytes to transfer
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(count * 2);
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}
