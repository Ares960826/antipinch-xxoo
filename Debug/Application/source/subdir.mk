################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/source/ADCTask.c \
../Application/source/AppIF.c \
../Application/source/EcumTask.c \
../Application/source/IRQCall.c \
../Application/source/Mcu.c \
../Application/source/WDGTask.c \
../Application/source/debug.c \
../Application/source/delay.c \
../Application/source/lowpower.c \
../Application/source/main.c \
../Application/source/xl6600_intr.c 

OBJS += \
./Application/source/ADCTask.o \
./Application/source/AppIF.o \
./Application/source/EcumTask.o \
./Application/source/IRQCall.o \
./Application/source/Mcu.o \
./Application/source/WDGTask.o \
./Application/source/debug.o \
./Application/source/delay.o \
./Application/source/lowpower.o \
./Application/source/main.o \
./Application/source/xl6600_intr.o 

C_DEPS += \
./Application/source/ADCTask.d \
./Application/source/AppIF.d \
./Application/source/EcumTask.d \
./Application/source/IRQCall.d \
./Application/source/Mcu.d \
./Application/source/WDGTask.d \
./Application/source/debug.d \
./Application/source/delay.d \
./Application/source/lowpower.d \
./Application/source/main.d \
./Application/source/xl6600_intr.d 


# Each subdirectory must supply rules for building sources it contributes
Application/source/%.o: ../Application/source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\002_ASW" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\source\Lin" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Startup" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Flash\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Driver\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\OS\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Trace\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_lowlevel" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_cfg" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_diagnostic" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_driver" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_transport" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\001_ComHeader" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


