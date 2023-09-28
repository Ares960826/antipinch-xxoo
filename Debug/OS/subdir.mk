################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../OS/OS.c \
../OS/Task.c 

OBJS += \
./OS/OS.o \
./OS/Task.o 

C_DEPS += \
./OS/OS.d \
./OS/Task.d 


# Each subdirectory must supply rules for building sources it contributes
OS/%.o: ../OS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\002_ASW" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\source\Lin" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Startup" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Flash\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Driver\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\OS\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Trace\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_lowlevel" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_cfg" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_diagnostic" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_driver" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_transport" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\001_ComHeader" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


