################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/usart/usart.c 

OBJS += \
./Hardware/usart/usart.o 

C_DEPS += \
./Hardware/usart/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/usart/%.o Hardware/usart/%.su: ../Hardware/usart/%.c Hardware/usart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Hardware-2f-usart

clean-Hardware-2f-usart:
	-$(RM) ./Hardware/usart/usart.d ./Hardware/usart/usart.o ./Hardware/usart/usart.su

.PHONY: clean-Hardware-2f-usart

