################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include OS/subdir.mk
-include Lin_Stack/Lin_transport/subdir.mk
-include Lin_Stack/Lin_lowlevel/subdir.mk
-include Lin_Stack/Lin_driver/subdir.mk
-include Lin_Stack/Lin_diagnostic/subdir.mk
-include Lin_Stack/Lin_core/subdir.mk
-include Lin_Stack/Lin_cfg/subdir.mk
-include Flash/subdir.mk
-include Driver/source/subdir.mk
-include Cmsis/Startup/subdir.mk
-include Application/source/Lin/subdir.mk
-include Application/source/002_ASW/subdir.mk
-include Application/source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
ChipWay_STEC_Window_Lifter_Sample.hex \

SECONDARY_SIZE += \
ChipWay_STEC_Window_Lifter_Sample.siz \


# All Target
all: ChipWay_STEC_Window_Lifter_Sample.elf secondary-outputs

# Tool invocations
ChipWay_STEC_Window_Lifter_Sample.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "D:\Programs\c2e-workspace\ChipWay_STEC_Window_Lifter_Sample\xl6600_flash.ld" -Xlinker --gc-sections -Wl,-Map,"ChipWay_STEC_Window_Lifter_Sample.map" --specs=nosys.specs -v -o "ChipWay_STEC_Window_Lifter_Sample.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ChipWay_STEC_Window_Lifter_Sample.hex: ChipWay_STEC_Window_Lifter_Sample.elf
	@echo 'Invoking: GNU ARM Cross Create Flash Image'
	arm-none-eabi-objcopy -O ihex "ChipWay_STEC_Window_Lifter_Sample.elf"  "ChipWay_STEC_Window_Lifter_Sample.hex"
	@echo 'Finished building: $@'
	@echo ' '

ChipWay_STEC_Window_Lifter_Sample.siz: ChipWay_STEC_Window_Lifter_Sample.elf
	@echo 'Invoking: GNU ARM Cross Print Size'
	arm-none-eabi-size --format=berkeley "ChipWay_STEC_Window_Lifter_Sample.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) ChipWay_STEC_Window_Lifter_Sample.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
