#include "led.h" // <>는 라이브러리에 있는 파일을 가져올 때, 현재 디렉터리에 있는 파일을 가져올 때는 "" 사용
//#include "button.h"
//
//void led_main(void);
//void led_all_on(void);
//void led_all_off(void);
//void led_on_sequential(void);
//void led_off_sequential(void);
//void led_on_up(void);
//void led_on_down(void);
//void led_keep_on_up(void);
//void led_keep_on_down(void);
//void flower_on(void);
//void flower_off(void);
//
//extern volatile int t1ms_counter; // main.c에 선언된 변수를 여기에서도 사용한다는 의미에서 "extern" 키워드 추가, 초기값은 제거하지 않으면 redefined 에러 발생
//
//void button0_led_all_on_off_toggle(void)
//{
//	static int button0_count = 0; // static으로 선언을 하면 전역변수처럼 동작한다
//
//	// 버튼을 한번 눌렀다 뗸 상태라면
//	if(get_button(BUTTON_0_GPIO_Port, BUTTON_0_Pin, 0) == BUTTON_ACTIVE)
//	{
//		button0_count++;
//		button0_count %= 2;
//		if(button0_count)
//		{
//			led_all_on();
//		}
//		else
//		{
//			led_all_off();
//		}
//	}
//}
//
//void button0_toggle(void)
//{
//	static int button0_count = 0; // static으로 선언을 하면 전역변수처럼 동작한다
//	static void (*fp[8])(void) = {led_all_on, led_all_off, flower_on, flower_off, led_keep_on_up, led_keep_on_down, led_on_up, led_on_down}; // 함수 포인터 테이블을 사용한다
//
//	// 버튼을 한번 눌렀다 뗸 상태라면
//	if(get_button(BUTTON_0_GPIO_Port, BUTTON_0_Pin, 0) == BUTTON_ACTIVE)
//	{
//		button0_count++;
//		button0_count %= 8;
//	}
//	fp[button0_count]();
//}
//
//void buttons_led_bar_up_down(void)
//{
//
//}
//
//int func_indicator = 0;
//
//void led_main(void)
//{
//	while(1)
//	{
//#if 0
////		button0_led_all_on_off_toggle();
////		button0_toggle();
//		buttons_led_bar_up_down();
//#endif
//
//#if 1
//#define LED_ALL_ON 0
//#define LED_ALL_OFF 1
//#define FLOWER_ON 2
//#define FLOWER_OFF 3
//#define LED_KEEP_ON_UP 4
//#define LED_KEEP_ON_DOWN 5
//#define LED_ON_UP 6
//#define LED_ON_DOWN 7
//		switch(func_indicator)
//		{
//		case LED_ALL_ON:
//			led_all_on();
//			break;
//		case LED_ALL_OFF:
//			led_all_off();
//			break;
//		case FLOWER_ON:
//			flower_on();
//			break;
//		case FLOWER_OFF:
//			flower_off();
//			break;
//		case LED_KEEP_ON_UP:
//			led_keep_on_up();
//			break;
//		case LED_KEEP_ON_DOWN:
//			led_keep_on_down();
//			break;
//		case LED_ON_UP:
//			led_on_up();
//			break;
//		case LED_ON_DOWN:
//			led_on_down();
//		}
//#endif
//
//#if 0
//#define LED_ON_UP 0
//#define LED_ON_DOWN 1
//		switch(func_indicator)
//		{
//		case LED_ON_UP:
//			led_on_up();
//			break;
//		case LED_ON_DOWN:
//			led_on_down();
//		}
//#endif
//
//#if 0
//		// 기본적인 Timer 예제와 사용하는 코드
//		if(t1ms_counter >= 200)
//		{
//			t1ms_counter = 0;
//			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);  // LED1
//			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);  // LED2
//			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); // LED3
//		}
//#endif
//
//#if 0
//		// phase 1
//		led_all_on();
//		HAL_Delay(500); // Sleep시킨다
//		led_all_off();
//		HAL_Delay(100); // Sleep시킨다
//#endif
//
//#if 0
//		// phase 2
//		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_All);
//		HAL_Delay(500);
//#endif
//
//#if 0
//		// phase 3
//		led_on_sequential();
//		led_off_sequential();
//#endif
//
//#if 0
//		// phase 4
//		// LED 점멸 순서: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 (200ms delay 후 전부 점등)
//		led_on_up();
//		led_all_off();
//		HAL_Delay(500);
//		// 2회차 점멸 순서: 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1 -> 0
//		led_on_down();
//		led_all_off();
//		HAL_Delay(500);
//#endif
//
//#if 0
//		// phase 5
//		// LED 점멸 순서: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
//		// 앞전에 ON 했던 LED는 그대로 유지
//		led_keep_on_up();
//		// 2회차 점멸 순서: 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1 -> 0
//		// 앞전에 ON 했던 LED는 그대로 유지
//		led_keep_on_down();
//#endif
//
//#if 0
//		// phase 6
//		flower_on();
//		flower_off();
//		HAL_Delay(50);
//#endif
//	}
//}
//
//void led_all_on(void)
//{
//#if 1
//	if(t1ms_counter > 200)
//	{
//		t1ms_counter = 0; // clear counter
//		HAL_GPIO_WritePin(GPIOD, 0xff, 1);
//		func_indicator = LED_ALL_OFF;
//	}
//#else
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
////		GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 1); // LED_BAR_1~8, 1 == GPIO_PIN_SET
//	HAL_GPIO_WritePin(GPIOD, 0xff, 1);
//#endif
//}
//
//void led_all_off(void)
//{
//#if 1
//	if(t1ms_counter > 200)
//	{
//		t1ms_counter = 0; // clear counter
//		HAL_GPIO_WritePin(GPIOD, 0xff, 0);
//		func_indicator = FLOWER_ON;
//	}
//#else
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET); // LED_BAR_1
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET); // LED_BAR_2
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET); // LED_BAR_3
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET); // LED_BAR_4
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET); // LED_BAR_5
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET); // LED_BAR_6
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET); // LED_BAR_7
////	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET); // LED_BAR_8
//
//	HAL_GPIO_WritePin(GPIOD, 0xff, 0);
//#endif
//}
//
//void flower_on(void)
//{
//	static int i = 0;
//#if 1 // Use timer interrupt instead of HAL_Delay
//	if(t1ms_counter > 200)
//	{
//		t1ms_counter = 0; // clear counter
//		led_all_off();
//		HAL_GPIO_WritePin(GPIOD, 0x10 << i, 1);
//		HAL_GPIO_WritePin(GPIOD, 0x08 >> i, 1);
//		i++;
//		if(i > 4)
//		{
//			i = 0;
//			func_indicator = FLOWER_OFF;
//		}
//	}
//#else
//	led_all_off();
//	for(int i = 0; i < 4; i++)
//	{
//		HAL_GPIO_WritePin(GPIOD, 0x10 << i, 1);
//		HAL_GPIO_WritePin(GPIOD, 0x08 >> i, 1);
//		HAL_Delay((i+1) * 100);
//	}
//
//	int prev_a = 0x00, prev_b = 0x00;
//	for(int i = 0; i < 4; i++)
//	{
//		led_all_off();
//		prev_a = prev_a | (0x10 << i);
//		prev_b = prev_b | (0x08 >> i);
//		HAL_GPIO_WritePin(GPIOD, prev_a | prev_b, 1);
//		HAL_Delay((i+1) * 100);
//	}
//#endif
//}
//
//void flower_off(void)
//{
//	static int i = 0;
//#if 1 // Use timer interrupt instead of HAL_Delay
//	if(t1ms_counter > 200)
//	{
//		t1ms_counter = 0; // clear counter
//		led_all_off();
//		HAL_GPIO_WritePin(GPIOD, 0x80 >> i, 0);
//		HAL_GPIO_WritePin(GPIOD, 0x01 << i, 0);
//		i++;
//		if(i > 4)
//		{
//			i = 0;
//			func_indicator = LED_KEEP_ON_UP;
//		}
//	}
//#else
//	led_all_on();
//	for(int i = 0; i < 4; i++)
//	{
//		HAL_GPIO_WritePin(GPIOD, 0x80 >> i, 0);
//		HAL_GPIO_WritePin(GPIOD, 0x01 << i, 0);
//		HAL_Delay((i+1) * 100);
//	}
//
//	int prev_a = 0xf0, prev_b = 0x0f;
//	for(int i = 0; i < 4; i++)
//	{
//		led_all_off();
//		HAL_GPIO_WritePin(GPIOD, prev_a | prev_b, 1);
//		prev_a = prev_a & (0xf0 >> (i+1));
//		prev_b = prev_b & ~(0x01 << i);
//		HAL_Delay(i * 100);
//	}
//#endif
//}
//
//void led_keep_on_up(void)
//{
//	static int i = 0;
//#if 1 // Use timer interrupt instead of HAL_Delay
//	if(t1ms_counter > 200)
//	{
//		t1ms_counter = 0; // clear counter
//		HAL_GPIO_WritePin(GPIOD, 0x01 << i, 1);
//		i++;
//		if(i > 7)
//		{
//			i = 0;
//			func_indicator = LED_KEEP_ON_DOWN;
//		}
//	}
//#else
////	int prev = 0x00;
//	led_all_off();
//	for(int i = 0; i < 8; i++)
//	{
////		led_all_off();
////		prev = (prev) | (0x01 << i);
////		HAL_GPIO_WritePin(GPIOD, prev, 1);
////		HAL_Delay(200);
//
//		// simplified of above
//		HAL_GPIO_WritePin(GPIOD, 0x01 << i, 1);
//		HAL_Delay(200);
//	}
//#endif
//}
//
//void led_keep_on_down(void)
//{
//	static int i = 0;
//#if 1 // Use timer interrupt instead of HAL_Delay
//	if(t1ms_counter > 200)
//	{
//		if(i == 0)
//		{
//			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
//		}
//		t1ms_counter = 0; // clear counter
//		HAL_GPIO_WritePin(GPIOD, 0x80 >> i, 1);
//		i++;
//		if(i > 7)
//		{
//			i = 0;
//			func_indicator = LED_ON_UP;
//		}
//	}
//#else
////	int prev = 0x00;
//	led_all_off();
//	for(int i = 0; i < 8; i++)
//	{
////		led_all_off();
////		prev = (prev) | (0x80 >> i);
////		HAL_GPIO_WritePin(GPIOD, prev, 1);
////		HAL_Delay(200);
//
//		// simplified of above
//		HAL_GPIO_WritePin(GPIOD, 0x80 >> i, 1);
//		HAL_Delay(200);
//	}
//#endif
//}
//
//void led_on_up(void)
//{
//	static int i = 0;
//#if 1 // Use timer interrupt instead of HAL_Delay
//	if(t1ms_counter > 200)
//	{
//		HAL_GPIO_WritePin(GPIOD, 0xff, 0);
//		t1ms_counter = 0; // clear counter
//		HAL_GPIO_WritePin(GPIOD, 0x01 << i, 1);
//		i++;
//		if(i > 7)
//		{
//			i = 0;
//			func_indicator = LED_ON_DOWN;
//		}
//	}
//#else // original
//	for(int i = 0; i < 8; i++)
//	{
//		led_all_off();
//		HAL_GPIO_WritePin(GPIOD, 0x01 << i, 1);
//		HAL_Delay(200);
//	}
//	led_all_off();
//#endif
//}
//
//void led_on_down(void)
//{
//	static int i = 0;
//#if 1
//	if(t1ms_counter > 200)
//	{
//		HAL_GPIO_WritePin(GPIOD, 0xff, 0);
//		t1ms_counter = 0; // clear counter
//		HAL_GPIO_WritePin(GPIOD, 0x80 >> i, 1);
//		i++;
//		if(i > 7)
//		{
//			i = 0;
//			func_indicator = LED_ALL_ON;
//		}
//	}
//#else
//	for(int i = 0; i < 8; i++)
//	{
//		led_all_off();
//		HAL_GPIO_WritePin(GPIOD, 0x80 >> i, 1);
//		HAL_Delay(200);
//	}
//	led_all_off();
//#endif
//}
//
//void led_on_sequential(void)
//{
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, 1);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, 1);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 1);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, 1);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 1);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 1);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 1);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 1);
//	HAL_Delay(200);
//}
//
//void led_off_sequential(void)
//{
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 0);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 0);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 0);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 0);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, 0);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, 0);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, 0);
//	HAL_Delay(200);
//}
