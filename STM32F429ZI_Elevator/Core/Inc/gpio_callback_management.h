#ifndef _GPIO__CALLBACK__MANAGEMENT_H_
#define _GPIO__CALLBACK__MANAGEMENT_H_

#include "main.h" // 버튼 조작에 필요한 HAL_Driver나 GPIO 정보가 모두 main.h에 있음


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


#endif /*_GPIO__CALLBACK__MANAGEMENT_H_*/
