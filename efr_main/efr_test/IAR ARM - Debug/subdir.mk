################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LSM6_i2c.c \
../ble-soc-bookkeeping.c \
../ble-soc-callback-stubs.c \
../ble-soc-callbacks.c \
../ble-soc-events.c \
../gatt_db.c 

OBJS += \
./LSM6_i2c.o \
./ble-soc-bookkeeping.o \
./ble-soc-callback-stubs.o \
./ble-soc-callbacks.o \
./ble-soc-events.o \
./gatt_db.o 

C_DEPS += \
./LSM6_i2c.d \
./ble-soc-bookkeeping.d \
./ble-soc-callback-stubs.d \
./ble-soc-callbacks.d \
./ble-soc-events.d \
./gatt_db.d 


# Each subdirectory must supply rules for building sources it contributes
LSM6_i2c.o: ../LSM6_i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --no_wrap_diagnostics -I"C:\Users\mfonk\git\marbl\marbl_efr32\inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\app_hw_inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\platform_hw\EFR32_inc" -e --cpu Cortex-M4F --fpu VFPv4_sp --debug --dlib_config "C:\Program Files (x86)\IAR-Systems\Embedded-Workbench-7.4\arm\inc\c\DLib_Config_Normal.h" --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling --dependencies=m "$(basename $(notdir $<)).d"
	@echo 'Finished building: $<'
	@echo ' '

ble-soc-bookkeeping.o: ../ble-soc-bookkeeping.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --no_wrap_diagnostics -I"C:\Users\mfonk\git\marbl\marbl_efr32\inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\app_hw_inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\platform_hw\EFR32_inc" -e --cpu Cortex-M4F --fpu VFPv4_sp --debug --dlib_config "C:\Program Files (x86)\IAR-Systems\Embedded-Workbench-7.4\arm\inc\c\DLib_Config_Normal.h" --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling --dependencies=m "$(basename $(notdir $<)).d"
	@echo 'Finished building: $<'
	@echo ' '

ble-soc-callback-stubs.o: ../ble-soc-callback-stubs.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --no_wrap_diagnostics -I"C:\Users\mfonk\git\marbl\marbl_efr32\inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\app_hw_inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\platform_hw\EFR32_inc" -e --cpu Cortex-M4F --fpu VFPv4_sp --debug --dlib_config "C:\Program Files (x86)\IAR-Systems\Embedded-Workbench-7.4\arm\inc\c\DLib_Config_Normal.h" --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling --dependencies=m "$(basename $(notdir $<)).d"
	@echo 'Finished building: $<'
	@echo ' '

ble-soc-callbacks.o: ../ble-soc-callbacks.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --no_wrap_diagnostics -I"C:\Users\mfonk\git\marbl\marbl_efr32\inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\app_hw_inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\platform_hw\EFR32_inc" -e --cpu Cortex-M4F --fpu VFPv4_sp --debug --dlib_config "C:\Program Files (x86)\IAR-Systems\Embedded-Workbench-7.4\arm\inc\c\DLib_Config_Normal.h" --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling --dependencies=m "$(basename $(notdir $<)).d"
	@echo 'Finished building: $<'
	@echo ' '

ble-soc-events.o: ../ble-soc-events.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --no_wrap_diagnostics -I"C:\Users\mfonk\git\marbl\marbl_efr32\inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\app_hw_inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\platform_hw\EFR32_inc" -e --cpu Cortex-M4F --fpu VFPv4_sp --debug --dlib_config "C:\Program Files (x86)\IAR-Systems\Embedded-Workbench-7.4\arm\inc\c\DLib_Config_Normal.h" --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling --dependencies=m "$(basename $(notdir $<)).d"
	@echo 'Finished building: $<'
	@echo ' '

gatt_db.o: ../gatt_db.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --no_wrap_diagnostics -I"C:\Users\mfonk\git\marbl\marbl_efr32\inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\app_hw_inc" -I"C:\Users\mfonk\git\marbl\marbl_efr32\platform_hw\EFR32_inc" -e --cpu Cortex-M4F --fpu VFPv4_sp --debug --dlib_config "C:\Program Files (x86)\IAR-Systems\Embedded-Workbench-7.4\arm\inc\c\DLib_Config_Normal.h" --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling --dependencies=m "$(basename $(notdir $<)).d"
	@echo 'Finished building: $<'
	@echo ' '


