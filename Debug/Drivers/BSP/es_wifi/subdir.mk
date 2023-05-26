################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/es_wifi/es_wifi.c 

OBJS += \
./Drivers/BSP/es_wifi/es_wifi.o 

C_DEPS += \
./Drivers/BSP/es_wifi/es_wifi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/es_wifi/%.o: ../Drivers/BSP/es_wifi/%.c Drivers/BSP/es_wifi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DGENERICMQTT -DUSE_MBED_TLS -DUSE_WIFI -DARM_MATH_CM4 -D__FPU_PRESENT=1U -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Middlewares/Third_Party -I../Middlewares -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/Common/include" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/GenericMQTT/Inc" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/Wifi/inlcude" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Drivers/BSP/es_wifi" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/cJSON" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/MQTTClient-C" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/MQTTPacket" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/STM32_MotionSP_Library/Inc" -I../MEMS/App -I../MEMS/Target -I../Drivers/BSP/B-L475E-IOT01A1 -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/lsm6dsl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

