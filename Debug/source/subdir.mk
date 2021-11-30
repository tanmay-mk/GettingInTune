################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/adc.c \
../source/autocorrelate.c \
../source/dac.c \
../source/dma.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sinx.c \
../source/test_sinx.c \
../source/tone.c \
../source/tpm.c 

OBJS += \
./source/adc.o \
./source/autocorrelate.o \
./source/dac.o \
./source/dma.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sinx.o \
./source/test_sinx.o \
./source/tone.o \
./source/tpm.o 

C_DEPS += \
./source/adc.d \
./source/autocorrelate.d \
./source/dac.d \
./source/dma.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sinx.d \
./source/test_sinx.d \
./source/tone.d \
./source/tpm.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu90 -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\board" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\source" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\drivers" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\CMSIS" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\utilities" -I"C:\Users\tanma\Documents\MCUXpressoIDE_11.2.0_4120\PES_Assignments\Getting In Tune\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


