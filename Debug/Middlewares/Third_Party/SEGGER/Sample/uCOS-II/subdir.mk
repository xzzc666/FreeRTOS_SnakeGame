################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/SEGGER/Sample/uCOS-II/SEGGER_SYSVIEW_uCOSII.c 

C_DEPS += \
./Middlewares/Third_Party/SEGGER/Sample/uCOS-II/SEGGER_SYSVIEW_uCOSII.d 

OBJS += \
./Middlewares/Third_Party/SEGGER/Sample/uCOS-II/SEGGER_SYSVIEW_uCOSII.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/SEGGER/Sample/uCOS-II/%.o Middlewares/Third_Party/SEGGER/Sample/uCOS-II/%.su Middlewares/Third_Party/SEGGER/Sample/uCOS-II/%.cyclo: ../Middlewares/Third_Party/SEGGER/Sample/uCOS-II/%.c Middlewares/Third_Party/SEGGER/Sample/uCOS-II/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"C:/Users/dongz/STM32CubeIDE/workspace_1.19.0/SnakeGameV0.0.1/Middlewares/Third_Party/SEGGER" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Sample-2f-uCOS-2d-II

clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Sample-2f-uCOS-2d-II:
	-$(RM) ./Middlewares/Third_Party/SEGGER/Sample/uCOS-II/SEGGER_SYSVIEW_uCOSII.cyclo ./Middlewares/Third_Party/SEGGER/Sample/uCOS-II/SEGGER_SYSVIEW_uCOSII.d ./Middlewares/Third_Party/SEGGER/Sample/uCOS-II/SEGGER_SYSVIEW_uCOSII.o ./Middlewares/Third_Party/SEGGER/Sample/uCOS-II/SEGGER_SYSVIEW_uCOSII.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Sample-2f-uCOS-2d-II

