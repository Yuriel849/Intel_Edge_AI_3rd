#include "led.h" // <>는 라이브러리에 있는 파일을 가져올 때, 현재 디렉터리에 있는 파일을 가져올 때는 "" 사용
#include "button.h"

void led_main(void);

void led_main(void)
{
	while(1)
	{
		// 버튼을 한번 눌렀다 뗀 상태라면
		if (get_button(BTN0_GPIO_Port, BTN0_Pin, 0) == BUTTON_PRESS)
		{
			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
		}
		if (get_button(BTN1_GPIO_Port, BTN1_Pin, 1) == BUTTON_PRESS)
		{
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}
		if (get_button(BTN2_GPIO_Port, BTN2_Pin, 2) == BUTTON_PRESS)
		{
			HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		}
		if (get_button(BTN3_GPIO_Port, BTN3_Pin, 3) == BUTTON_PRESS)
		{
			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);   // LED1
		}
	}
}

