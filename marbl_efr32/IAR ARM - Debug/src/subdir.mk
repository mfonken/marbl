################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/InitDevice.c 

OBJS += \
./src/InitDevice.o 

C_DEPS += \
./src/InitDevice.d 


# Each subdirectory must supply rules for building sources it contributes
src/InitDevice.o: ../src/InitDevice.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --no_wrap_diagnostics -I"C:\Users\mfonk\SimplicityStudio\v3_workspace\marbl_efr32-standalone-radio-config\inc" -e --cpu Cortex-M4F --fpu VFPv4_sp --debug --dlib_config "C:\Program Files (x86)\IAR-Systems\Embedded-Workbench-7.4\arm\inc\c\DLib_Config_Normal.h" --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling --dependencies=m "$(basename $(notdir $<)).d"
	@echo 'Finished building: $<'
	@echo ' '


