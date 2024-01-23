#include "gpio_callback_management.h"

volatile int external_interrupt = -1;

/*
 * 포토 센서 익스터널 인터럽트 콜백
 * copy from "/root/Drivers/STM32F4xx_HAL_Driver/Src/stm324f4xx_hal_gpio.c"
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//	switch (GPIO_Pin)
//	{
//		case PhotoSensorEXTI0_Pin:
//			external_interrupt = GPIO_Pin;
//			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
//			break;
//		case PhotoSensorEXTI1_Pin:
//			external_interrupt = GPIO_Pin;
//			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
//			break;
//		case PhotoSensorEXTI2_Pin:
//			external_interrupt = GPIO_Pin;
//			HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
//			break;
//		default:
//			break;
//	}
}
