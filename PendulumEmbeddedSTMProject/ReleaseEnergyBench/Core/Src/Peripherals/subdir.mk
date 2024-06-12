################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Peripherals/gpio.c \
../Core/Src/Peripherals/i2c.c \
../Core/Src/Peripherals/tim.c \
../Core/Src/Peripherals/usart.c 

C_DEPS += \
./Core/Src/Peripherals/gpio.d \
./Core/Src/Peripherals/i2c.d \
./Core/Src/Peripherals/tim.d \
./Core/Src/Peripherals/usart.d 

OBJS += \
./Core/Src/Peripherals/gpio.o \
./Core/Src/Peripherals/i2c.o \
./Core/Src/Peripherals/tim.o \
./Core/Src/Peripherals/usart.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Peripherals/%.o Core/Src/Peripherals/%.su Core/Src/Peripherals/%.cyclo: ../Core/Src/Peripherals/%.c Core/Src/Peripherals/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Benchmark" -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Pendulum" -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Peripherals" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Peripherals

clean-Core-2f-Src-2f-Peripherals:
	-$(RM) ./Core/Src/Peripherals/gpio.cyclo ./Core/Src/Peripherals/gpio.d ./Core/Src/Peripherals/gpio.o ./Core/Src/Peripherals/gpio.su ./Core/Src/Peripherals/i2c.cyclo ./Core/Src/Peripherals/i2c.d ./Core/Src/Peripherals/i2c.o ./Core/Src/Peripherals/i2c.su ./Core/Src/Peripherals/tim.cyclo ./Core/Src/Peripherals/tim.d ./Core/Src/Peripherals/tim.o ./Core/Src/Peripherals/tim.su ./Core/Src/Peripherals/usart.cyclo ./Core/Src/Peripherals/usart.d ./Core/Src/Peripherals/usart.o ./Core/Src/Peripherals/usart.su

.PHONY: clean-Core-2f-Src-2f-Peripherals

