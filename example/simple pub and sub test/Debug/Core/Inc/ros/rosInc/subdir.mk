################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/ros/rosInc/duration.cpp \
../Core/Inc/ros/rosInc/time.cpp 

OBJS += \
./Core/Inc/ros/rosInc/duration.o \
./Core/Inc/ros/rosInc/time.o 

CPP_DEPS += \
./Core/Inc/ros/rosInc/duration.d \
./Core/Inc/ros/rosInc/time.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/ros/rosInc/%.o: ../Core/Inc/ros/rosInc/%.cpp Core/Inc/ros/rosInc/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

