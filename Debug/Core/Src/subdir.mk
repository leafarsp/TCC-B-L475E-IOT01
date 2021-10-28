################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/VibrationMonitoring.c \
../Core/Src/bsp.c \
../Core/Src/dfsdm.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/rng.c \
../Core/Src/rtc.c \
../Core/Src/sensor_def.c \
../Core/Src/spi.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/tim.c 

OBJS += \
./Core/Src/VibrationMonitoring.o \
./Core/Src/bsp.o \
./Core/Src/dfsdm.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/rng.o \
./Core/Src/rtc.o \
./Core/Src/sensor_def.o \
./Core/Src/spi.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/tim.o 

C_DEPS += \
./Core/Src/VibrationMonitoring.d \
./Core/Src/bsp.d \
./Core/Src/dfsdm.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/rng.d \
./Core/Src/rtc.d \
./Core/Src/sensor_def.d \
./Core/Src/spi.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DGENERICMQTT -DUSE_MBED_TLS -DUSE_WIFI -DARM_MATH_CM4 -D__FPU_PRESENT=1U -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Middlewares/Third_Party -I../Middlewares -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/Common/include" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/GenericMQTT/Inc" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/Wifi/inlcude" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Drivers/BSP/es_wifi" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/cJSON" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/MQTTClient-C" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/MQTTPacket" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/STM32_MotionSP_Library/Inc" -I../MEMS/App -I../MEMS/Target -I../Drivers/BSP/B-L475E-IOT01A1 -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/lsm6dsl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

