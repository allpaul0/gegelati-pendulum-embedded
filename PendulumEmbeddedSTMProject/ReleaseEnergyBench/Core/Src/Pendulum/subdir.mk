################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Pendulum/TPGGraph.c \
../Core/Src/Pendulum/TPGPrograms.c 

CPP_SRCS += \
../Core/Src/Pendulum/PendulumExecutionEnvironment.cpp 

C_DEPS += \
./Core/Src/Pendulum/TPGGraph.d \
./Core/Src/Pendulum/TPGPrograms.d 

OBJS += \
./Core/Src/Pendulum/PendulumExecutionEnvironment.o \
./Core/Src/Pendulum/TPGGraph.o \
./Core/Src/Pendulum/TPGPrograms.o 

CPP_DEPS += \
./Core/Src/Pendulum/PendulumExecutionEnvironment.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Pendulum/%.o Core/Src/Pendulum/%.su Core/Src/Pendulum/%.cyclo: ../Core/Src/Pendulum/%.cpp Core/Src/Pendulum/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DDEBUG -DSTM32 -DTYPE_INT=0 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Benchmark" -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Pendulum" -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Peripherals" -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Pendulum/%.o Core/Src/Pendulum/%.su Core/Src/Pendulum/%.cyclo: ../Core/Src/Pendulum/%.c Core/Src/Pendulum/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Benchmark" -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Pendulum" -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Peripherals" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Pendulum

clean-Core-2f-Src-2f-Pendulum:
	-$(RM) ./Core/Src/Pendulum/PendulumExecutionEnvironment.cyclo ./Core/Src/Pendulum/PendulumExecutionEnvironment.d ./Core/Src/Pendulum/PendulumExecutionEnvironment.o ./Core/Src/Pendulum/PendulumExecutionEnvironment.su ./Core/Src/Pendulum/TPGGraph.cyclo ./Core/Src/Pendulum/TPGGraph.d ./Core/Src/Pendulum/TPGGraph.o ./Core/Src/Pendulum/TPGGraph.su ./Core/Src/Pendulum/TPGPrograms.cyclo ./Core/Src/Pendulum/TPGPrograms.d ./Core/Src/Pendulum/TPGPrograms.o ./Core/Src/Pendulum/TPGPrograms.su

.PHONY: clean-Core-2f-Src-2f-Pendulum

