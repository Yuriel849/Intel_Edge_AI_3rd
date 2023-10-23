################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Cmp/button_cmp.c \
../Core/Cmp/internal_rtc_cmp.c \
../Core/Cmp/main_cmp.c 

OBJS += \
./Core/Cmp/button_cmp.o \
./Core/Cmp/internal_rtc_cmp.o \
./Core/Cmp/main_cmp.o 

C_DEPS += \
./Core/Cmp/button_cmp.d \
./Core/Cmp/internal_rtc_cmp.d \
./Core/Cmp/main_cmp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Cmp/%.o Core/Cmp/%.su Core/Cmp/%.cyclo: ../Core/Cmp/%.c Core/Cmp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Cmp

clean-Core-2f-Cmp:
	-$(RM) ./Core/Cmp/button_cmp.cyclo ./Core/Cmp/button_cmp.d ./Core/Cmp/button_cmp.o ./Core/Cmp/button_cmp.su ./Core/Cmp/internal_rtc_cmp.cyclo ./Core/Cmp/internal_rtc_cmp.d ./Core/Cmp/internal_rtc_cmp.o ./Core/Cmp/internal_rtc_cmp.su ./Core/Cmp/main_cmp.cyclo ./Core/Cmp/main_cmp.d ./Core/Cmp/main_cmp.o ./Core/Cmp/main_cmp.su

.PHONY: clean-Core-2f-Cmp

