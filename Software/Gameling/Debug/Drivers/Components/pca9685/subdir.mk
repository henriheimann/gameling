################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/pca9685/pca9685.c 

OBJS += \
./Drivers/Components/pca9685/pca9685.o 

C_DEPS += \
./Drivers/Components/pca9685/pca9685.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/pca9685/%.o: ../Drivers/Components/pca9685/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L412xx -I"/Users/Henri/Development/Private/Embedded/STM32/Gameling/Inc" -I"/Users/Henri/Development/Private/Embedded/STM32/Gameling/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/Users/Henri/Development/Private/Embedded/STM32/Gameling/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/Henri/Development/Private/Embedded/STM32/Gameling/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/Henri/Development/Private/Embedded/STM32/Gameling/Drivers/CMSIS/Include" -I"/Users/Henri/Development/Private/Embedded/STM32/Gameling/Drivers/Components" -I"/Users/Henri/Development/Private/Embedded/STM32/Gameling/Application"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


