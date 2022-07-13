################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/DEV_Config.c \
../Core/Inc/GUI_Paint.c \
../Core/Inc/LCD_1in8.c \
../Core/Inc/LCD_1inch8_test.c \
../Core/Inc/image.c 

OBJS += \
./Core/Inc/DEV_Config.o \
./Core/Inc/GUI_Paint.o \
./Core/Inc/LCD_1in8.o \
./Core/Inc/LCD_1inch8_test.o \
./Core/Inc/image.o 

C_DEPS += \
./Core/Inc/DEV_Config.d \
./Core/Inc/GUI_Paint.d \
./Core/Inc/LCD_1in8.d \
./Core/Inc/LCD_1inch8_test.d \
./Core/Inc/image.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o Core/Inc/%.su: ../Core/Inc/%.c Core/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F410Rx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc

clean-Core-2f-Inc:
	-$(RM) ./Core/Inc/DEV_Config.d ./Core/Inc/DEV_Config.o ./Core/Inc/DEV_Config.su ./Core/Inc/GUI_Paint.d ./Core/Inc/GUI_Paint.o ./Core/Inc/GUI_Paint.su ./Core/Inc/LCD_1in8.d ./Core/Inc/LCD_1in8.o ./Core/Inc/LCD_1in8.su ./Core/Inc/LCD_1inch8_test.d ./Core/Inc/LCD_1inch8_test.o ./Core/Inc/LCD_1inch8_test.su ./Core/Inc/image.d ./Core/Inc/image.o ./Core/Inc/image.su

.PHONY: clean-Core-2f-Inc

