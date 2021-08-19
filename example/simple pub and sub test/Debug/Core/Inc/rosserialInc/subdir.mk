################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/rosserialInc/duration.cpp \
../Core/Inc/rosserialInc/rosserialNode.cpp \
../Core/Inc/rosserialInc/time.cpp 

OBJS += \
./Core/Inc/rosserialInc/duration.o \
./Core/Inc/rosserialInc/rosserialNode.o \
./Core/Inc/rosserialInc/time.o 

CPP_DEPS += \
./Core/Inc/rosserialInc/duration.d \
./Core/Inc/rosserialInc/rosserialNode.d \
./Core/Inc/rosserialInc/time.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/rosserialInc/%.o: ../Core/Inc/rosserialInc/%.cpp Core/Inc/rosserialInc/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"/home/softarm/STM32CubeIDE/workspace_1.7.0/rosserial_stm32cxj_example/Core/Inc/rosserialInc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

