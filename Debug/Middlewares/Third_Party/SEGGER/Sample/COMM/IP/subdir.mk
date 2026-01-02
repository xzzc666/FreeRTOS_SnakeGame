################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/SEGGER/Sample/COMM/IP/SEGGER_SYSVIEW_COMM_IP_embOS_emNet.c 

C_DEPS += \
./Middlewares/Third_Party/SEGGER/Sample/COMM/IP/SEGGER_SYSVIEW_COMM_IP_embOS_emNet.d 

OBJS += \
./Middlewares/Third_Party/SEGGER/Sample/COMM/IP/SEGGER_SYSVIEW_COMM_IP_embOS_emNet.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/SEGGER/Sample/COMM/IP/%.o Middlewares/Third_Party/SEGGER/Sample/COMM/IP/%.su Middlewares/Third_Party/SEGGER/Sample/COMM/IP/%.cyclo: ../Middlewares/Third_Party/SEGGER/Sample/COMM/IP/%.c Middlewares/Third_Party/SEGGER/Sample/COMM/IP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"C:/Users/dongz/STM32CubeIDE/workspace_1.19.0/SnakeGameV0.0.1/Middlewares/Third_Party/SEGGER" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Sample-2f-COMM-2f-IP

clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Sample-2f-COMM-2f-IP:
	-$(RM) ./Middlewares/Third_Party/SEGGER/Sample/COMM/IP/SEGGER_SYSVIEW_COMM_IP_embOS_emNet.cyclo ./Middlewares/Third_Party/SEGGER/Sample/COMM/IP/SEGGER_SYSVIEW_COMM_IP_embOS_emNet.d ./Middlewares/Third_Party/SEGGER/Sample/COMM/IP/SEGGER_SYSVIEW_COMM_IP_embOS_emNet.o ./Middlewares/Third_Party/SEGGER/Sample/COMM/IP/SEGGER_SYSVIEW_COMM_IP_embOS_emNet.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Sample-2f-COMM-2f-IP

