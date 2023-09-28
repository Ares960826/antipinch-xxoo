################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/source/Lin/AppLin.c \
../Application/source/Lin/LinDcm.c \
../Application/source/Lin/LinDcm_Cfg.c 

OBJS += \
./Application/source/Lin/AppLin.o \
./Application/source/Lin/LinDcm.o \
./Application/source/Lin/LinDcm_Cfg.o 

C_DEPS += \
./Application/source/Lin/AppLin.d \
./Application/source/Lin/LinDcm.d \
./Application/source/Lin/LinDcm_Cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Application/source/Lin/%.o: ../Application/source/Lin/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\002_ASW" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\source\Lin" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Startup" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Flash\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Driver\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\OS\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Trace\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_lowlevel" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_cfg" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_diagnostic" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_driver" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_transport" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\001_ComHeader" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


