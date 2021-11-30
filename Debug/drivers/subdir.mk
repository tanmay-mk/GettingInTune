################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_cmp.c \
../drivers/fsl_common.c \
../drivers/fsl_dac.c \
../drivers/fsl_dma.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_flash.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpsci.c \
../drivers/fsl_lpsci_dma.c \
../drivers/fsl_smc.c \
../drivers/fsl_tpm.c \
../drivers/fsl_tsi_v4.c \
../drivers/fsl_uart.c \
../drivers/fsl_uart_dma.c 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_cmp.o \
./drivers/fsl_common.o \
./drivers/fsl_dac.o \
./drivers/fsl_dma.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_flash.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpsci.o \
./drivers/fsl_lpsci_dma.o \
./drivers/fsl_smc.o \
./drivers/fsl_tpm.o \
./drivers/fsl_tsi_v4.o \
./drivers/fsl_uart.o \
./drivers/fsl_uart_dma.o 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_cmp.d \
./drivers/fsl_common.d \
./drivers/fsl_dac.d \
./drivers/fsl_dma.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_flash.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpsci.d \
./drivers/fsl_lpsci_dma.d \
./drivers/fsl_smc.d \
./drivers/fsl_tpm.d \
./drivers/fsl_tsi_v4.d \
./drivers/fsl_uart.d \
./drivers/fsl_uart_dma.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu90 -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\board" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\source" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\drivers" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\CMSIS" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\utilities" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


