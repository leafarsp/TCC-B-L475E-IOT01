################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/lsm6dsl/lsm6dsl.c \
../Drivers/BSP/Components/lsm6dsl/lsm6dsl_reg.c 

OBJS += \
./Drivers/BSP/Components/lsm6dsl/lsm6dsl.o \
./Drivers/BSP/Components/lsm6dsl/lsm6dsl_reg.o 

C_DEPS += \
./Drivers/BSP/Components/lsm6dsl/lsm6dsl.d \
./Drivers/BSP/Components/lsm6dsl/lsm6dsl_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/lsm6dsl/%.o: ../Drivers/BSP/Components/lsm6dsl/%.c Drivers/BSP/Components/lsm6dsl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -D__FPU_PRESENT=1U -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/STM32_MotionSP_Library/Inc" -I../MEMS/App -I../MEMS/Target -I../Drivers/BSP/B-L475E-IOT01A1 -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/lsm6dsl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

