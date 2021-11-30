/*
 * PES Assignment 7
 *
 * File Name: adc.c
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */

/*	LIBRARY FILES	*/
#include "MKL25Z4.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "fsl_debug_console.h"

/*	OTHER FILES TO BE INCLUDED	*/
#include "autocorrelate.h"
#include "adc.h"
#include "tpm.h"

/*
 * @brief: see documentation in adc.h
 */
void ADC_Init() {
	// Gating
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	// normal power mode, no clock divide, long sampling enabled, 16-bit conversion (single-ended), use bus clock
	ADC0->CFG1 = ADC_CFG1_ADLPC(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_ADLSMP(0) | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0);

	// Set the ADC0 configuration 2 register
	ADC0->CFG2 = 0;

	// DMA initially disabled
	ADC0->SC2 = ADC_SC2_ADTRG(1) | ADC_SC2_ACFE(0) | ADC_SC2_DMAEN(0) | ADC_SC2_REFSEL(0);

	// Input Channel for DAC is the input for ADC
	ADC0->SC1[0] = ADC_SC1_AIEN(0) | ADC_SC1_DIFF(0) | ADC_SC1_ADCH(23);

	// Enable ADC0 triggering from TPM1 overflow
	SIM->SOPT7 = SIM_SOPT7_ADC0ALTTRGEN(1) | SIM_SOPT7_ADC0TRGSEL(9);

} //ADC_Init_()

/*
 * @brief: see documentation in adc.h
 */
void ADC_Buffer(uint16_t *buffer, uint32_t count)
{
	int i =0;

	// Begin TPM
	BEGIN_TPM1

	for (i = 0; i < count; i++)
	{
		while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		      ;
		buffer[i] = ADC0->R[0];
	}

	// Stop Sampling
	STOP_TPM1

} //ADC_Buffer


/*
 * @brief: see documentation in adc.h
 */
void analysis(uint16_t *buffer, uint32_t count)
{
	int i=0;
	uint32_t max, sum = 0;
	int min;

	min = buffer[0];
	max = buffer[0];

	for (i=0; i < count; i++)
	{
		//if next number is greater than previously computed maximum number
		//then set next number as maximum number
		if (buffer[i] > max)
		{
			max = buffer[i];
		}

		//if next number is lesser than previously computed minimum number
		//then set next number as minimum number
		if (buffer[i] < min)
		{
			min = buffer[i];
		}
		sum+= buffer[i];
	}

	//calculate the average of the entire buffer
	int avg = sum/count;

	//get period from autocorrelate function
	int period = autocorrelate_detect_period(buffer, count, kAC_16bps_unsigned);

	//compute frequency
	int frequency = ADC_SAMPLING_FREQUENCY / period;

	//print all computations
	PRINTF("min=%u max=%u avg=%u period=%d frequency=%d Hz\r\n\n",
			min,   max,   avg,   period,   frequency);

} //analysis

void calibrate_ADC()
{
	//Initialize or clear a 16-bit variable in RAM.
	uint16_t status = 0;

	//enable software trigger
	ADC0->SC2 = ADC_SC2_ADTRG(0);
	//disable ADCO and AVGS bit in ADC0 Status Control 3 register
	ADC0->SC3 &= (~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK);
	//Hardware function enabled
	ADC0->SC3 |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(0));
	//Start Calibration
	ADC0->SC3 |= ADC_SC3_CAL_MASK;
	//Wait for calibration to be completed
	while ((ADC0->SC1[0] & ADC_SC1_COCO_MASK ) == 0);

	if((ADC0->SC3 & ADC_SC3_CALF_MASK) == ADC_SC3_CALF_MASK)
	{
		PRINTF("\n\rADC Calibration Failed\n\r");
	}
	else
	{
		PRINTF("\n\rADC Calibration Successful\n\r");
	}
	//Calculate plus-side calibration value
	//Add the plus-side calibration results CLP0, CLP1, CLP2, CLP3, CLP4, and CLPS to the variable
	status = (ADC0->CLP0 & ADC_CLP0_CLP0_MASK) + (ADC0->CLP1 & ADC_CLP1_CLP1_MASK) + (ADC0->CLP2 & ADC_CLP2_CLP2_MASK) + (ADC0->CLP3 & ADC_CLP3_CLP3_MASK) + (ADC0->CLP4 & ADC_CLP4_CLP4_MASK) + (ADC0->CLPS & ADC_CLPS_CLPS_MASK);
	//Divide the variable by two
	status = status / 2;
	//Set the MSB of the variable
	status |= 0x8000;
	//Store the value in the plus-side gain calibration register PG
	ADC0->PG = ADC_PG_PG(status);

	status = 0;

	//Calculate minus-side calibration value
	status = (ADC0->CLM0 & ADC_CLM0_CLM0_MASK) + (ADC0->CLM1 & ADC_CLM1_CLM1_MASK) + (ADC0->CLM2 & ADC_CLM2_CLM2_MASK) + (ADC0->CLM3 & ADC_CLM3_CLM3_MASK) + (ADC0->CLM4 & ADC_CLM4_CLM4_MASK) + (ADC0->CLMS & ADC_CLMS_CLMS_MASK);
	status = status / 2;
	status |= 0x8000;

	ADC0->MG = ADC_MG_MG(status);
	//Clear CAL bit
	ADC0->SC3 &= ~ADC_SC3_CAL_MASK;
} //calibrate_ADC
