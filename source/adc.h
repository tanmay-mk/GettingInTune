
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

#define SYS_CLOCK		(48e6)

#define ADC_SAMPLING_FREQUENCY 96000
#define ADC_BUFFER_SIZE 1024

#define BEGIN_TPM1 TPM1->SC |= TPM_SC_CMOD(1);
#define STOP_TPM1  TPM1->SC &= ~TPM_SC_CMOD_MASK;

void ADC_Init_();

void ADC_Buffer(uint16_t *buffer, uint32_t sample_count);

void analysis(uint16_t *buffer, uint32_t count);


#endif
