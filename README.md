# PES-Assignment-7

The project is to be run in DEBUG mode only. 

Names of files: 
main.c
adc.h/.c
autocorrelate.h/.c
dac.h/.c
dma.h/.c
sinx.h/.c
test_sinx.h/.c
tone.h/.c
tpm.h/.c

In the DMA IRQ handler function, the interrupt rollover variable that is being used to run the wave for 1 sec is done such that the values that are being compared to the rollover are downscaled to a certain value in order to make a transition every one second. 
These downscaled numbers are not defined as 'macros'.

UART Configuration parameters for debug:
Baud Rate: 115200
Data size: 8 bits
Parity: None
Stop bits: 1
Encoding: Default (ISO-8859-1)

For extra credit #1
Calibration of ADC is implemented and is called in main.c
The function is declared in adc.h and defined in adc.c