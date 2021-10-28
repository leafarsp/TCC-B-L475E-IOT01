################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/cJSON/subdir.mk
-include Middlewares/Third_Party/MbedTLS/source/subdir.mk
-include Middlewares/Third_Party/MQTTPacket/subdir.mk
-include Middlewares/Third_Party/MQTTClient-C/subdir.mk
-include Middlewares/STM32_MotionSP_Library/Src/subdir.mk
-include MEMS/Target/subdir.mk
-include MEMS/App/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/CommonTables/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/subdir.mk
-include Drivers/BSP/es_wifi/subdir.mk
-include Drivers/BSP/Components/lsm6dsl/subdir.mk
-include Drivers/BSP/B-L475E-IOT01A1/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Application/Wifi/source/subdir.mk
-include Application/GenericMQTT/Src/subdir.mk
-include Application/Common/source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := GatewayWegnologyFFT
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
GatewayWegnologyFFT.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
GatewayWegnologyFFT.list \

OBJCOPY_BIN += \
GatewayWegnologyFFT.bin \


# All Target
all: main-build

# Main-build Target
main-build: GatewayWegnologyFFT.elf secondary-outputs

# Tool invocations
GatewayWegnologyFFT.elf: $(OBJS) $(USER_OBJS) D:\TCC\B-L475E-IOT01A\GatewayWegnologyFFT\STM32L475VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "GatewayWegnologyFFT.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\TCC\B-L475E-IOT01A\GatewayWegnologyFFT\STM32L475VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="GatewayWegnologyFFT.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

GatewayWegnologyFFT.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "GatewayWegnologyFFT.list"
	@echo 'Finished building: $@'
	@echo ' '

GatewayWegnologyFFT.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "GatewayWegnologyFFT.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SIZE_OUTPUT)$(OBJDUMP_LIST)$(EXECUTABLES)$(OBJS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(OBJCOPY_BIN) GatewayWegnologyFFT.elf
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
