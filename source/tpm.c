/*
 * PES Assignment 7
 *
 * File Name: tpm.c
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */

/*	OTHER FILES TO BE INCLUDED	*/
#include "tpm.h"
#include "dac.h"

/*
 * @brief: see documentation in tpm.h
 */
void TPM0_Init() {

	// Gating
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	// 48 Mhz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	// Begin Configuration
	TPM0->SC = 0;

	// Load the mod and counter
	TPM0->MOD = TPM_MOD_MOD(1000);
	TPM0->CNT = 0;

	// TPM Source Configuration
	TPM0->SC = TPM_SC_PS(0) | TPM_SC_CPWMS(0) | TPM_SC_CMOD(1) | TPM_SC_DMA_MASK;
}

/*
 * @brief: see documentation in tpm.h
 */
void TPM1_Init(int sample) {

	// Clock Gating
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

	// Disable TPM for config
	TPM1->SC = 0;

    // mod and counter
	TPM1->MOD = TPM_MOD_MOD(SYS_CLOCK / sample);
	TPM1->CNT = 0;

	// Prescalar Settings
	TPM1->SC = TPM_SC_PS(0) | TPM_SC_CPWMS(0);

}
