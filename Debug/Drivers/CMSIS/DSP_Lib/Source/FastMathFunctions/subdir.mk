################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_f32.c \
../Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q15.c \
../Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q31.c \
../Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_f32.c \
../Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q15.c \
../Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q31.c \
../Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q15.c \
../Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.c 

OBJS += \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_f32.o \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q15.o \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q31.o \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_f32.o \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q15.o \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q31.o \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q15.o \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.o 

C_DEPS += \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_f32.d \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q15.d \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q31.d \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_f32.d \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q15.d \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q31.d \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q15.d \
./Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/%.o: ../Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/%.c Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -D__FPU_PRESENT=1U -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I"D:/TCC/B-L475E-IOT01A/GatewayWegnologyFFT/Middlewares/STM32_MotionSP_Library/Inc" -I../MEMS/App -I../MEMS/Target -I../Drivers/BSP/B-L475E-IOT01A1 -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/lsm6dsl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

