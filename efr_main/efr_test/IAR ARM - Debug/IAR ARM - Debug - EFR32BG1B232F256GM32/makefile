################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include platform_hw/EFR32/subdir.mk
-include platform/subdir.mk
-include idle-sleep/subdir.mk
-include app_hw/subdir.mk
-include app/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S79_DEPS)),)
-include $(S79_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(MSA_UPPER_DEPS)),)
-include $(MSA_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(MSA_DEPS)),)
-include $(MSA_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S79_UPPER_DEPS)),)
-include $(S79_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pre-build main-build

# Main-build Target
main-build: marbl_efr32-standalone-radio-config.out

# Tool invocations
marbl_efr32-standalone-radio-config.out: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: IAR Linker for ARM'
	ilinkarm $(OBJS) $(USER_OBJS) -o "marbl_efr32-standalone-radio-config.out" --config "C:\Users\mfonk\SimplicityStudio\v3_workspace\marbl_efr32-standalone-radio-config\bleDemo.icf" --no_wrap_diagnostics "C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/lib/emdrv.a" "C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/lib/emlib.a" "C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/lib/wstk.a" "C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/lib/ble_stack.a" "C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/lib/linklayer.a" "C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/lib/radio.a"  
	ielftool --ihex --verbose "marbl_efr32-standalone-radio-config.out" "marbl_efr32-standalone-radio-config.hex"  
	ielftool --ihex "marbl_efr32-standalone-radio-config.out" "marbl_efr32-standalone-radio-config.hex" 
	ielftool --bin "marbl_efr32-standalone-radio-config.out" "marbl_efr32-standalone-radio-config.bin" 
	ielftool --srec "marbl_efr32-standalone-radio-config.out" "marbl_efr32-standalone-radio-config.s37"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(S79_DEPS)$(S_DEPS)$(CXX_DEPS)$(MSA_UPPER_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(CC_DEPS)$(MSA_DEPS)$(ASM_UPPER_DEPS)$(S79_UPPER_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS) marbl_efr32-standalone-radio-config.out
	-@echo ' '

pre-build:
	-C:\SiliconLabs\SimplicityStudio\v3\developer\toolchains\bgbuild\bgbuild.exe -ng C:\Users\mfonk\SimplicityStudio\v3_workspace\marbl_efr32-standalone-radio-config\.\ble-soc-gattdb.bgproj
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

-include ../makefile.targets
