################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.c \
../Middlewares/Third_Party/MQTTPacket/MQTTConnectServer.c \
../Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.c \
../Middlewares/Third_Party/MQTTPacket/MQTTFormat.c \
../Middlewares/Third_Party/MQTTPacket/MQTTPacket.c \
../Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.c \
../Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.c \
../Middlewares/Third_Party/MQTTPacket/MQTTSubscribeServer.c \
../Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.c \
../Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeServer.c 

OBJS += \
./Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.o \
./Middlewares/Third_Party/MQTTPacket/MQTTConnectServer.o \
./Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.o \
./Middlewares/Third_Party/MQTTPacket/MQTTFormat.o \
./Middlewares/Third_Party/MQTTPacket/MQTTPacket.o \
./Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.o \
./Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.o \
./Middlewares/Third_Party/MQTTPacket/MQTTSubscribeServer.o \
./Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.o \
./Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeServer.o 

C_DEPS += \
./Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.d \
./Middlewares/Third_Party/MQTTPacket/MQTTConnectServer.d \
./Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.d \
./Middlewares/Third_Party/MQTTPacket/MQTTFormat.d \
./Middlewares/Third_Party/MQTTPacket/MQTTPacket.d \
./Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.d \
./Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.d \
./Middlewares/Third_Party/MQTTPacket/MQTTSubscribeServer.d \
./Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.d \
./Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeServer.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/MQTTPacket/%.o: ../Middlewares/Third_Party/MQTTPacket/%.c Middlewares/Third_Party/MQTTPacket/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DGENERICMQTT -DUSE_MBED_TLS -DUSE_WIFI -DARM_MATH_CM4 -D__FPU_PRESENT=1U -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Middlewares/Third_Party -I../Middlewares -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/Common/include" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/GenericMQTT/Inc" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/Wifi/inlcude" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Drivers/BSP/es_wifi" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/cJSON" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/MQTTClient-C" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/MQTTPacket" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/STM32_MotionSP_Library/Inc" -I../MEMS/App -I../MEMS/Target -I../Drivers/BSP/B-L475E-IOT01A1 -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/lsm6dsl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

