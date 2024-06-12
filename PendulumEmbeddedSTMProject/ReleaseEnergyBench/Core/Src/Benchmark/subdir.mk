################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Benchmark/Bench.cpp \
../Core/Src/Benchmark/INA219Bench.cpp \
../Core/Src/Benchmark/INA219Monitor.cpp \
../Core/Src/Benchmark/Monitor.cpp \
../Core/Src/Benchmark/PendulumINA219Bench.cpp \
../Core/Src/Benchmark/PendulumINA219Monitor.cpp \
../Core/Src/Benchmark/TimeUnit.cpp \
../Core/Src/Benchmark/TimingBench.cpp 

OBJS += \
./Core/Src/Benchmark/Bench.o \
./Core/Src/Benchmark/INA219Bench.o \
./Core/Src/Benchmark/INA219Monitor.o \
./Core/Src/Benchmark/Monitor.o \
./Core/Src/Benchmark/PendulumINA219Bench.o \
./Core/Src/Benchmark/PendulumINA219Monitor.o \
./Core/Src/Benchmark/TimeUnit.o \
./Core/Src/Benchmark/TimingBench.o 

CPP_DEPS += \
./Core/Src/Benchmark/Bench.d \
./Core/Src/Benchmark/INA219Bench.d \
./Core/Src/Benchmark/INA219Monitor.d \
./Core/Src/Benchmark/Monitor.d \
./Core/Src/Benchmark/PendulumINA219Bench.d \
./Core/Src/Benchmark/PendulumINA219Monitor.d \
./Core/Src/Benchmark/TimeUnit.d \
./Core/Src/Benchmark/TimingBench.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Benchmark/%.o Core/Src/Benchmark/%.su Core/Src/Benchmark/%.cyclo: ../Core/Src/Benchmark/%.cpp Core/Src/Benchmark/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DDEBUG -DSTM32 -DTYPE_INT=0 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Benchmark" -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Pendulum" -I"/home/paulallaire/dev/gegelati-pendulum-embedded/gegelati-pendulum-embedded/PendulumEmbeddedSTMProject/Core/Inc/Peripherals" -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Benchmark

clean-Core-2f-Src-2f-Benchmark:
	-$(RM) ./Core/Src/Benchmark/Bench.cyclo ./Core/Src/Benchmark/Bench.d ./Core/Src/Benchmark/Bench.o ./Core/Src/Benchmark/Bench.su ./Core/Src/Benchmark/INA219Bench.cyclo ./Core/Src/Benchmark/INA219Bench.d ./Core/Src/Benchmark/INA219Bench.o ./Core/Src/Benchmark/INA219Bench.su ./Core/Src/Benchmark/INA219Monitor.cyclo ./Core/Src/Benchmark/INA219Monitor.d ./Core/Src/Benchmark/INA219Monitor.o ./Core/Src/Benchmark/INA219Monitor.su ./Core/Src/Benchmark/Monitor.cyclo ./Core/Src/Benchmark/Monitor.d ./Core/Src/Benchmark/Monitor.o ./Core/Src/Benchmark/Monitor.su ./Core/Src/Benchmark/PendulumINA219Bench.cyclo ./Core/Src/Benchmark/PendulumINA219Bench.d ./Core/Src/Benchmark/PendulumINA219Bench.o ./Core/Src/Benchmark/PendulumINA219Bench.su ./Core/Src/Benchmark/PendulumINA219Monitor.cyclo ./Core/Src/Benchmark/PendulumINA219Monitor.d ./Core/Src/Benchmark/PendulumINA219Monitor.o ./Core/Src/Benchmark/PendulumINA219Monitor.su ./Core/Src/Benchmark/TimeUnit.cyclo ./Core/Src/Benchmark/TimeUnit.d ./Core/Src/Benchmark/TimeUnit.o ./Core/Src/Benchmark/TimeUnit.su ./Core/Src/Benchmark/TimingBench.cyclo ./Core/Src/Benchmark/TimingBench.d ./Core/Src/Benchmark/TimingBench.o ./Core/Src/Benchmark/TimingBench.su

.PHONY: clean-Core-2f-Src-2f-Benchmark

