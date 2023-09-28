################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lin_Stack/Lin_core/lin_common_api.c \
../Lin_Stack/Lin_core/lin_common_proto.c \
../Lin_Stack/Lin_core/lin_j2602_api.c \
../Lin_Stack/Lin_core/lin_j2602_proto.c \
../Lin_Stack/Lin_core/lin_lin21_api.c \
../Lin_Stack/Lin_core/lin_lin21_proto.c 

OBJS += \
./Lin_Stack/Lin_core/lin_common_api.o \
./Lin_Stack/Lin_core/lin_common_proto.o \
./Lin_Stack/Lin_core/lin_j2602_api.o \
./Lin_Stack/Lin_core/lin_j2602_proto.o \
./Lin_Stack/Lin_core/lin_lin21_api.o \
./Lin_Stack/Lin_core/lin_lin21_proto.o 

C_DEPS += \
./Lin_Stack/Lin_core/lin_common_api.d \
./Lin_Stack/Lin_core/lin_common_proto.d \
./Lin_Stack/Lin_core/lin_j2602_api.d \
./Lin_Stack/Lin_core/lin_j2602_proto.d \
./Lin_Stack/Lin_core/lin_lin21_api.d \
./Lin_Stack/Lin_core/lin_lin21_proto.d 


# Each subdirectory must supply rules for building sources it contributes
Lin_Stack/Lin_core/%.o: ../Lin_Stack/Lin_core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\002_ASW" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\source\Lin" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Cmsis\Startup" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Flash\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Driver\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\OS\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Trace\include" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_lowlevel" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_cfg" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_core" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_diagnostic" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_driver" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Lin_Stack\Lin_transport" -I"D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\Application\include\001_ComHeader" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


