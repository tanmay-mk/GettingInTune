

#include "dac.h"
#include "MKL25Z4.h"
#include "stdio.h"
#include "string.h"

// Global Variables
uint16_t buffer[1024];
uint32_t count = 0;

#define DAC0_PIN 30


void DAC_Init_() {

	// Clock Gating
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK; // DAC
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// Pin and Port Setup
	PORTE->PCR[DAC0_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[DAC0_PIN] |= PORT_PCR_MUX(3);

	// // Not using DAC0 buffer, disable to use buffer
    DAC0->C1 = 0;
    DAC0->C2 = 0;

    // Set DAC0 to reference voltage from VDDA
    DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;

}



void DAC_begin(uint16_t *frequency, uint32_t cnt){

	// TPM Disable
	TPM0->SC &= ~TPM_SC_CMOD_MASK;

	// For interfacing with the global count function
	count = cnt;

	// Memory copy to buffer
	memcpy(buffer, frequency, cnt*2);

	// Begin Configuration
	TPM0->SC |= TPM_SC_CMOD(1);

	// Configure the src and dest registers
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) buffer);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));

	// Number of bytes to transfer
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(count * 2);
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}



