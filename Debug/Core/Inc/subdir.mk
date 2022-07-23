################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Control.c \
../Core/Inc/DEV_Config.c \
../Core/Inc/GUI_Paint.c \
../Core/Inc/LCD_1in8.c \
../Core/Inc/LCD_1inch8_test.c \
../Core/Inc/LCD_Routines.c \
../Core/Inc/PWM_Config.c \
../Core/Inc/SensorInterfacing.c \
../Core/Inc/image.c 

OBJS += \
./Core/Inc/Control.o \
./Core/Inc/DEV_Config.o \
./Core/Inc/GUI_Paint.o \
./Core/Inc/LCD_1in8.o \
./Core/Inc/LCD_1inch8_test.o \
./Core/Inc/LCD_Routines.o \
./Core/Inc/PWM_Config.o \
./Core/Inc/SensorInterfacing.o \
./Core/Inc/image.o 

C_DEPS += \
./Core/Inc/Control.d \
./Core/Inc/DEV_Config.d \
./Core/Inc/GUI_Paint.d \
./Core/Inc/LCD_1in8.d \
./Core/Inc/LCD_1inch8_test.d \
./Core/Inc/LCD_Routines.d \
./Core/Inc/PWM_Config.d \
./Core/Inc/SensorInterfacing.d \
./Core/Inc/image.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o Core/Inc/%.su: ../Core/Inc/%.c Core/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F410Rx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc

clean-Core-2f-Inc:
	-$(RM) ./Core/Inc/Control.d ./Core/Inc/Control.o ./Core/Inc/Control.su ./Core/Inc/DEV_Config.d ./Core/Inc/DEV_Config.o ./Core/Inc/DEV_Config.su ./Core/Inc/GUI_Paint.d ./Core/Inc/GUI_Paint.o ./Core/Inc/GUI_Paint.su ./Core/Inc/LCD_1in8.d ./Core/Inc/LCD_1in8.o ./Core/Inc/LCD_1in8.su ./Core/Inc/LCD_1inch8_test.d ./Core/Inc/LCD_1inch8_test.o ./Core/Inc/LCD_1inch8_test.su ./Core/Inc/LCD_Routines.d ./Core/Inc/LCD_Routines.o ./Core/Inc/LCD_Routines.su ./Core/Inc/PWM_Config.d ./Core/Inc/PWM_Config.o ./Core/Inc/PWM_Config.su ./Core/Inc/SensorInterfacing.d ./Core/Inc/SensorInterfacing.o ./Core/Inc/SensorInterfacing.su ./Core/Inc/image.d ./Core/Inc/image.o ./Core/Inc/image.su

.PHONY: clean-Core-2f-Inc

