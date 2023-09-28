################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/source/xl_acmp.c \
../Driver/source/xl_adc.c \
../Driver/source/xl_clm.c \
../Driver/source/xl_crc.c \
../Driver/source/xl_dma.c \
../Driver/source/xl_eeprom.c \
../Driver/source/xl_ewm.c \
../Driver/source/xl_flash.c \
../Driver/source/xl_ftm.c \
../Driver/source/xl_gpio.c \
../Driver/source/xl_i2c.c \
../Driver/source/xl_ics.c \
../Driver/source/xl_irq.c \
../Driver/source/xl_kbi.c \
../Driver/source/xl_mcan.c \
../Driver/source/xl_nvic.c \
../Driver/source/xl_osc.c \
../Driver/source/xl_pit.c \
../Driver/source/xl_pmc.c \
../Driver/source/xl_port.c \
../Driver/source/xl_pwt.c \
../Driver/source/xl_rtc.c \
../Driver/source/xl_sim.c \
../Driver/source/xl_spi.c \
../Driver/source/xl_uart.c \
../Driver/source/xl_wdog.c 

OBJS += \
./Driver/source/xl_acmp.o \
./Driver/source/xl_adc.o \
./Driver/source/xl_clm.o \
./Driver/source/xl_crc.o \
./Driver/source/xl_dma.o \
./Driver/source/xl_eeprom.o \
./Driver/source/xl_ewm.o \
./Driver/source/xl_flash.o \
./Driver/source/xl_ftm.o \
./Driver/source/xl_gpio.o \
./Driver/source/xl_i2c.o \
./Driver/source/xl_ics.o \
./Driver/source/xl_irq.o \
./Driver/source/xl_kbi.o \
./Driver/source/xl_mcan.o \
./Driver/source/xl_nvic.o \
./Driver/source/xl_osc.o \
./Driver/source/xl_pit.o \
./Driver/source/xl_pmc.o \
./Driver/source/xl_port.o \
./Driver/source/xl_pwt.o \
./Driver/source/xl_rtc.o \
./Driver/source/xl_sim.o \
./Driver/source/xl_spi.o \
./Driver/source/xl_uart.o \
./Driver/source/xl_wdog.o 

C_DEPS += \
./Driver/source/xl_acmp.d \
./Driver/source/xl_adc.d \
./Driver/source/xl_clm.d \
./Driver/source/xl_crc.d \
./Driver/source/xl_dma.d \
./Driver/source/xl_eeprom.d \
./Driver/source/xl_ewm.d \
./Driver/source/xl_flash.d \
./Driver/source/xl_ftm.d \
./Driver/source/xl_gpio.d \
./Driver/source/xl_i2c.d \
./Driver/source/xl_ics.d \
./Driver/source/xl_irq.d \
./Driver/source/xl_kbi.d \
./Driver/source/xl_mcan.d \
./Driver/source/xl_nvic.d \
./Driver/source/xl_osc.d \
./Driver/source/xl_pit.d \
./Driver/source/xl_pmc.d \
./Driver/source/xl_port.d \
./Driver/source/xl_pwt.d \
./Driver/source/xl_rtc.d \
./Driver/source/xl_sim.d \
./Driver/source/xl_spi.d \
./Driver/source/xl_uart.d \
./Driver/source/xl_wdog.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/source/%.o: ../Driver/source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\002_ASW" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\source\Lin" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Startup" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Flash\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Driver\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\OS\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Trace\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_lowlevel" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_cfg" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_diagnostic" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_driver" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_transport" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\001_ComHeader" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


