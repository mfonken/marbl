################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include protocol/bluetooth/lib/EFR32MG1P/IAR/subdir.mk
-include protocol/bluetooth/ble_stack/src/soc/subdir.mk
-include platform/micrium_os/ports/source/iar/subdir.mk
-include platform/micrium_os/ports/source/generic/subdir.mk
-include platform/micrium_os/kernel/source/subdir.mk
-include platform/micrium_os/cpu/source/subdir.mk
-include platform/micrium_os/common/source/rtos/subdir.mk
-include platform/micrium_os/common/source/platform_mgr/subdir.mk
-include platform/micrium_os/common/source/lib/subdir.mk
-include platform/micrium_os/common/source/kal/subdir.mk
-include platform/micrium_os/common/source/common/subdir.mk
-include platform/micrium_os/common/source/collections/subdir.mk
-include platform/micrium_os/bsp/siliconlabs/generic/source/subdir.mk
-include platform/emlib/src/subdir.mk
-include platform/emdrv/tempdrv/src/subdir.mk
-include platform/emdrv/sleep/src/subdir.mk
-include platform/Device/SiliconLabs/EFR32MG1P/Source/IAR/subdir.mk
-include platform/Device/SiliconLabs/EFR32MG1P/Source/subdir.mk
-include hardware/kit/common/drivers/subdir.mk
-include hardware/kit/common/bsp/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(MSA_UPPER_DEPS)),)
-include $(MSA_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S79_DEPS)),)
-include $(S79_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(MSA_DEPS)),)
-include $(MSA_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S79_UPPER_DEPS)),)
-include $(S79_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: soc-thermometer-rtos.out

# Tool invocations
soc-thermometer-rtos.out: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: IAR Linker for ARM'
	ilinkarm $(OBJS) $(USER_OBJS) -o "soc-thermometer-rtos.out" --config "C:\Users\Matthew Fonken\SimplicityStudio\v4_workspace\soc-thermometer-rtos\efr32mg1p732f256gm32.icf" --no_wrap_diagnostics "C:\Users\Matthew Fonken\SimplicityStudio\v4_workspace\soc-thermometer-rtos\protocol\bluetooth\lib\EFR32MG1P\IAR\libmbedtls.a" "C:\Users\Matthew Fonken\SimplicityStudio\v4_workspace\soc-thermometer-rtos\protocol\bluetooth\lib\EFR32MG1P\IAR\libpsstore.a" "C:\Users\Matthew Fonken\SimplicityStudio\v4_workspace\soc-thermometer-rtos\protocol\bluetooth\lib\EFR32MG1P\IAR\binapploader.o" "C:\Users\Matthew Fonken\SimplicityStudio\v4_workspace\soc-thermometer-rtos\protocol\bluetooth\lib\EFR32MG1P\IAR\libbluetooth.a" "C:\Users\Matthew Fonken\SimplicityStudio\v4_workspace\soc-thermometer-rtos\platform\radio\rail_lib\autogen\librail_release\librail_efr32xg1_iar_release.a" --entry __iar_program_start --no_range_reservations --keep __iar_program_start  
	ielftool --srec --verbose "soc-thermometer-rtos.out" "soc-thermometer-rtos.s37"  
	ielftool --ihex --verbose "soc-thermometer-rtos.out" "soc-thermometer-rtos.hex"  
	ielftool --bin --verbose "soc-thermometer-rtos.out" "soc-thermometer-rtos.bin"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(MSA_UPPER_DEPS)$(EXECUTABLES)$(OBJS)$(ASM_DEPS)$(S79_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(MSA_DEPS)$(C_DEPS)$(S79_UPPER_DEPS) soc-thermometer-rtos.out
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
