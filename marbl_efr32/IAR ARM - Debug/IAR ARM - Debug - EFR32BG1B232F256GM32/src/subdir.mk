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
	iccarm "$<" -o "$@" --enum_is_int --no_wrap_diagnostics -I"C:\Users\mfonk\SimplicityStudio\v3_workspace\marbl_efr32-standalone-radio-config\inc" -IC:/Users/mfonk/SimplicityStudio/v3_workspace/marbl_efr32-standalone-radio-config -I"C:\Users\mfonk\SimplicityStudio\v3_workspace\marbl_efr32-standalone-radio-config\app_hw_inc" -I"C:\Users\mfonk\SimplicityStudio\v3_workspace\marbl_efr32-standalone-radio-config\platform_hw\EFR32_inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emlib/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//sdk/plugins/app" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//sdk/plugins/app_hw" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//sdk/framework-soc/plugins/app_hw" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//sdk/plugins/platform" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//sdk/framework-soc/plugins/platform_hw" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/CMSIS/Include" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emdrv/common/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emdrv/config" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emdrv/dmadrv/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emdrv/gpiointerrupt/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emdrv/nvm/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emdrv/rtcdrv/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emdrv/sleep/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emdrv/spidrv/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emdrv/uartdrv/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/emdrv/ustimer/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/kits/common/bsp" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/kits/common/drivers" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/reptile/glib" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/reptile/glib/dmd" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/reptile/glib/dmd/ssd2119" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/reptile/glib/glib" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/wstk/inc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/ble_stack/inc/soc" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/ble_stack/inc/common" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//sdk/plugins/platform_hw" -I"C:/SiliconLabs/BluetoothSmartSDK/1.0.2.0-GA//modules/Device/SiliconLabs/efr32BG1B/Include" -e --cpu Cortex-M4F --fpu None --debug --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling '-DCONFIGURATION_HEADER="ble-soc-configuration.h"' '-DBOOKKEEPING_HEADER="ble-soc-bookkeeping.h"' '-DCALLBACKS_HEADER="ble-soc-callbacks.h"' '-DEFR32BG1B232F256GM32=1' --diag_suppress pa050 --diag_error pe223 --dependencies=m "$(basename $(notdir $<)).d"
	@echo 'Finished building: $<'
	@echo ' '


