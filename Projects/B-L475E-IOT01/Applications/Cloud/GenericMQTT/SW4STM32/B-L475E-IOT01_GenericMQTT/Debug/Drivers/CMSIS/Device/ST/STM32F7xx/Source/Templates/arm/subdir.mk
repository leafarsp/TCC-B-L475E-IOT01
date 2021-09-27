################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f722xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f723xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f732xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f733xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f745xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f746xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f756xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f765xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f767xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f769xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f777xx.s \
../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f779xx.s 

OBJS += \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f722xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f723xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f732xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f733xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f745xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f746xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f756xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f765xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f767xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f769xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f777xx.o \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f779xx.o 

S_DEPS += \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f722xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f723xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f732xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f733xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f745xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f746xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f756xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f765xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f767xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f769xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f777xx.d \
./Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/startup_stm32f779xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/%.o: ../Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/%.s Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"D:/TCC/B-L475E-IOT01A/STM32CubeExpansion_Cloud_CLD_GEN_V1.0.0/Projects/B-L475E-IOT01/Applications/Cloud/GenericMQTT/SW4STM32/B-L475E-IOT01_GenericMQTT/Middlewares/STM32_MotionSP_Library" -I"D:/TCC/B-L475E-IOT01A/STM32CubeExpansion_Cloud_CLD_GEN_V1.0.0/Projects/B-L475E-IOT01/Applications/Cloud/GenericMQTT/SW4STM32/B-L475E-IOT01_GenericMQTT/Middlewares/STM32_MotionSP_Library/Inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

