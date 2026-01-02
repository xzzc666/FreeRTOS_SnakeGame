################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_ARMv7_PMU.c \
../Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_Ultra_ARMv7_PMU.c 

C_DEPS += \
./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_ARMv7_PMU.d \
./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_Ultra_ARMv7_PMU.d 

OBJS += \
./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_ARMv7_PMU.o \
./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_Ultra_ARMv7_PMU.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/%.o Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/%.su Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/%.cyclo: ../Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/%.c Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"C:/Users/dongz/STM32CubeIDE/workspace_1.19.0/SnakeGameV0.0.1/Middlewares/Third_Party/SEGGER" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Sample-2f-embOS-2f-Config-2f-ARMv7_PMU

clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Sample-2f-embOS-2f-Config-2f-ARMv7_PMU:
	-$(RM) ./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_ARMv7_PMU.cyclo ./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_ARMv7_PMU.d ./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_ARMv7_PMU.o ./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_ARMv7_PMU.su ./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_Ultra_ARMv7_PMU.cyclo ./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_Ultra_ARMv7_PMU.d ./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_Ultra_ARMv7_PMU.o ./Middlewares/Third_Party/SEGGER/Sample/embOS/Config/ARMv7_PMU/SEGGER_SYSVIEW_Config_embOS_Ultra_ARMv7_PMU.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Sample-2f-embOS-2f-Config-2f-ARMv7_PMU

