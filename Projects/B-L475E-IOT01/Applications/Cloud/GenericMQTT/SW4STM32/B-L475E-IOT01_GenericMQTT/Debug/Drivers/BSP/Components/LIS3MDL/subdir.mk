################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/TCC/B-L475E-IOT01A/TCC_estudo_vibracao/Drivers/BSP/Components/lis3mdl/lis3mdl.c 

OBJS += \
./Drivers/BSP/Components/LIS3MDL/lis3mdl.o 

C_DEPS += \
./Drivers/BSP/Components/LIS3MDL/lis3mdl.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/LIS3MDL/lis3mdl.o: D:/TCC/B-L475E-IOT01A/TCC_estudo_vibracao/Drivers/BSP/Components/lis3mdl/lis3mdl.c Drivers/BSP/Components/LIS3MDL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L475xx -DUSE_HAL_DRIVER '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DGENERICMQTT -DUSE_MBED_TLS -DUSE_WIFI -DARM_MATH_CM4 -D__FPU_PRESENT=1U -c -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I"D:/TCC/B-L475E-IOT01A/TCC_estudo_vibracao/Projects/B-L475E-IOT01/Applications/Cloud/GenericMQTT/SW4STM32/B-L475E-IOT01_GenericMQTT/Drivers/BSP/Components/LSM6DSL" -I"D:/TCC/B-L475E-IOT01A/STM32CubeExpansion_Cloud_CLD_GEN_V1.0.0/Projects/B-L475E-IOT01/Applications/Cloud/GenericMQTT/SW4STM32/B-L475E-IOT01_GenericMQTT/Drivers/BSP/B-L475E-IOT01/Inc" -I"D:/TCC/B-L475E-IOT01A/TCC_estudo_vibracao/Projects/B-L475E-IOT01/Applications/Cloud/GenericMQTT/SW4STM32/B-L475E-IOT01_GenericMQTT/Middlewares/STM32_MotionSP_Library/Inc" -I../../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/B-L475E-IOT01 -I../../../Inc -I../../../../../../../Common/GenericMQTT/Inc -I../../../../../../../Common/Shared/Inc -I../../../../../../../../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src -I../../../../../../../../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src -I../../../../../../../../Middlewares/Third_Party/mbedTLS/include -I../../../../../../../../Middlewares/Third_Party/cJSON -I../../../../../../../../Drivers/BSP/Components/es_wifi -I../../../../../../../../Drivers/BSP/Components/hts221 -I../../../../../../../../Drivers/BSP/Components/lis3mdl -I../../../../../../../../Drivers/BSP/Components/lps22hb -I../../../../../../../../Drivers/BSP/Components/lsm6dsl -I../../../../../../../../Drivers/BSP/Components/vl53l0x -I"D:/TCC/B-L475E-IOT01A/STM32CubeExpansion_Cloud_CLD_GEN_V1.0.0/Drivers/CMSIS/Include" -I"D:/TCC/B-L475E-IOT01A/TCC_estudo_vibracao/Projects/B-L475E-IOT01/Applications/Cloud/GenericMQTT/SW4STM32/B-L475E-IOT01_GenericMQTT/Middlewares/STM32_MotionSP_Library" -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

