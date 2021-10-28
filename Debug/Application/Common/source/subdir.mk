################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Common/source/STM32CubeRTCInterface.c \
../Application/Common/source/c2c_net.c \
../Application/Common/source/cloud.c \
../Application/Common/source/entropy_hardware_poll.c \
../Application/Common/source/flash_l4.c \
../Application/Common/source/heap.c \
../Application/Common/source/http_util.c \
../Application/Common/source/iot_flash_config.c \
../Application/Common/source/lwip_net.c \
../Application/Common/source/mbedtls_net.c \
../Application/Common/source/net.c \
../Application/Common/source/net_tcp_c2c.c \
../Application/Common/source/net_tcp_lwip.c \
../Application/Common/source/net_tcp_wifi.c \
../Application/Common/source/net_tls_mbedtls.c \
../Application/Common/source/paho_timer.c \
../Application/Common/source/rfu.c \
../Application/Common/source/sensors_data.c \
../Application/Common/source/timedate.c \
../Application/Common/source/timingSystem.c \
../Application/Common/source/wifi_net.c 

OBJS += \
./Application/Common/source/STM32CubeRTCInterface.o \
./Application/Common/source/c2c_net.o \
./Application/Common/source/cloud.o \
./Application/Common/source/entropy_hardware_poll.o \
./Application/Common/source/flash_l4.o \
./Application/Common/source/heap.o \
./Application/Common/source/http_util.o \
./Application/Common/source/iot_flash_config.o \
./Application/Common/source/lwip_net.o \
./Application/Common/source/mbedtls_net.o \
./Application/Common/source/net.o \
./Application/Common/source/net_tcp_c2c.o \
./Application/Common/source/net_tcp_lwip.o \
./Application/Common/source/net_tcp_wifi.o \
./Application/Common/source/net_tls_mbedtls.o \
./Application/Common/source/paho_timer.o \
./Application/Common/source/rfu.o \
./Application/Common/source/sensors_data.o \
./Application/Common/source/timedate.o \
./Application/Common/source/timingSystem.o \
./Application/Common/source/wifi_net.o 

C_DEPS += \
./Application/Common/source/STM32CubeRTCInterface.d \
./Application/Common/source/c2c_net.d \
./Application/Common/source/cloud.d \
./Application/Common/source/entropy_hardware_poll.d \
./Application/Common/source/flash_l4.d \
./Application/Common/source/heap.d \
./Application/Common/source/http_util.d \
./Application/Common/source/iot_flash_config.d \
./Application/Common/source/lwip_net.d \
./Application/Common/source/mbedtls_net.d \
./Application/Common/source/net.d \
./Application/Common/source/net_tcp_c2c.d \
./Application/Common/source/net_tcp_lwip.d \
./Application/Common/source/net_tcp_wifi.d \
./Application/Common/source/net_tls_mbedtls.d \
./Application/Common/source/paho_timer.d \
./Application/Common/source/rfu.d \
./Application/Common/source/sensors_data.d \
./Application/Common/source/timedate.d \
./Application/Common/source/timingSystem.d \
./Application/Common/source/wifi_net.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Common/source/%.o: ../Application/Common/source/%.c Application/Common/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DGENERICMQTT -DUSE_MBED_TLS -DUSE_WIFI -DARM_MATH_CM4 -D__FPU_PRESENT=1U -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Middlewares/Third_Party -I../Middlewares -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/Common/include" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/GenericMQTT/Inc" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Application/Wifi/inlcude" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Drivers/BSP/es_wifi" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/cJSON" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/MQTTClient-C" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/Third_Party/MQTTPacket" -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/STM32_MotionSP_Library/Inc" -I../MEMS/App -I../MEMS/Target -I../Drivers/BSP/B-L475E-IOT01A1 -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/lsm6dsl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

