################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/source/002_ASW/FlashApManage.c \
../Application/source/002_ASW/Hallpos.c \
../Application/source/002_ASW/KeyPort.c \
../Application/source/002_ASW/TestMode.c \
../Application/source/002_ASW/Ubat.c \
../Application/source/002_ASW/apfunc.c \
../Application/source/002_ASW/apparam.c \
../Application/source/002_ASW/appl_const.c \
../Application/source/002_ASW/motor.c \
../Application/source/002_ASW/param.c \
../Application/source/002_ASW/relay.c \
../Application/source/002_ASW/sub_task.c \
../Application/source/002_ASW/switch_925.c \
../Application/source/002_ASW/sysfunc.c \
../Application/source/002_ASW/syst_security.c \
../Application/source/002_ASW/thermo.c 

O_SRCS += \
../Application/source/002_ASW/aplib.o 

OBJS += \
./Application/source/002_ASW/FlashApManage.o \
./Application/source/002_ASW/Hallpos.o \
./Application/source/002_ASW/KeyPort.o \
./Application/source/002_ASW/TestMode.o \
./Application/source/002_ASW/Ubat.o \
./Application/source/002_ASW/apfunc.o \
./Application/source/002_ASW/apparam.o \
./Application/source/002_ASW/appl_const.o \
./Application/source/002_ASW/motor.o \
./Application/source/002_ASW/param.o \
./Application/source/002_ASW/relay.o \
./Application/source/002_ASW/sub_task.o \
./Application/source/002_ASW/switch_925.o \
./Application/source/002_ASW/sysfunc.o \
./Application/source/002_ASW/syst_security.o \
./Application/source/002_ASW/thermo.o 

C_DEPS += \
./Application/source/002_ASW/FlashApManage.d \
./Application/source/002_ASW/Hallpos.d \
./Application/source/002_ASW/KeyPort.d \
./Application/source/002_ASW/TestMode.d \
./Application/source/002_ASW/Ubat.d \
./Application/source/002_ASW/apfunc.d \
./Application/source/002_ASW/apparam.d \
./Application/source/002_ASW/appl_const.d \
./Application/source/002_ASW/motor.d \
./Application/source/002_ASW/param.d \
./Application/source/002_ASW/relay.d \
./Application/source/002_ASW/sub_task.d \
./Application/source/002_ASW/switch_925.d \
./Application/source/002_ASW/sysfunc.d \
./Application/source/002_ASW/syst_security.d \
./Application/source/002_ASW/thermo.d 


# Each subdirectory must supply rules for building sources it contributes
Application/source/002_ASW/%.o: ../Application/source/002_ASW/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\002_ASW" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\source\Lin" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Startup" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Flash\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Driver\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\OS\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Trace\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_lowlevel" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_cfg" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_diagnostic" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_driver" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_transport" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\001_ComHeader" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


