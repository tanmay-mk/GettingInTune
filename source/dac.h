

#ifndef DAC_H_
#define DAC_H_

#include "MKL25Z4.h"
#include "stdio.h"
#include "stdint.h"

/*
 * DAC Frequency
 */
#define SAMPLING_FREQUENCY			(48000)
/*
 * System Clock Hz
 */
#define SYS_CLOCK		(48e6)

extern uint16_t buffer[1024];
extern uint32_t count;

void DAC_Init_();

void DAC_begin(uint16_t *frq, uint32_t cnt);

//void DAC_end();

#endif /* DAC_H_ */
