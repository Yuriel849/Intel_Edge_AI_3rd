#include "led_final.h" // <>는 라이브러리에 있는 파일을 가져올 때, 현재 디렉터리에 있는 파일을 가져올 때는 "" 사용
#include "button.h"

void led_main(void);
void led_all_on(void);
void led_all_off(void);
void led_on_sequential(void);
void led_off_sequential(void);
void led_on_up(void);
void led_on_down(void);
void led_keep_on_up(void);
void led_keep_on_down(void);
void flower_on(void);
void flower_off(void);

extern volatile int t1ms_counter; // main.c에 선언된 변수를 여기에서도 사용한다는 의미에서 "extern" 키워드 추가, 초기값은 제거하지 않으면 redefined 에러 발생

int func_indicator = 0;

void led_final_main(void)
{
	while(1)
	{
//		button0_led_all_on_off_toggle();
//		button0_toggle();
//		buttons_led_bar_up_down();

#define LED_ALL_ON 0
#define LED_ALL_OFF 1
#define FLOWER_ON 2
#define FLOWER_OFF 3
#define LED_KEEP_ON_UP 4
#define LED_KEEP_ON_DOWN 5
#define LED_ON_UP 6
#define LED_ON_DOWN 7
		switch(func_indicator)
		{
		case LED_ALL_ON:
			led_all_on();
			break;
		case LED_ALL_OFF:
			led_all_off();
			break;
		case FLOWER_ON:
			flower_on();
			break;
		case FLOWER_OFF:
			flower_off();
			break;
		case LED_KEEP_ON_UP:
			led_keep_on_up();
			break;
		case LED_KEEP_ON_DOWN:
			led_keep_on_down();
			break;
		case LED_ON_UP:
			led_on_up();
			break;
		case LED_ON_DOWN:
			led_on_down();
		}
	}
}

void led_all_on(void)
{
	if(t1ms_counter > 200)
	{
		t1ms_counter = 0; // clear counter
		HAL_GPIO_WritePin(GPIOD, 0xff, 1);
		if(get_button(BUTTON_0_GPIO_Port, BUTTON_0_Pin, 0) == BUTTON_ACTIVE)
		{
			func_indicator = LED_ALL_OFF;
		}
	}
}

void led_all_off(void)
{
	if(t1ms_counter > 200)
	{
		t1ms_counter = 0; // clear counter
		HAL_GPIO_WritePin(GPIOD, 0xff, 0);
		if(get_button(BUTTON_0_GPIO_Port, BUTTON_0_Pin, 0) == BUTTON_ACTIVE)
		{
			func_indicator = FLOWER_ON;
		}
	}
}

void flower_on(void)
{
	static int i = 0;
	if(t1ms_counter > 200)
	{
		t1ms_counter = 0; // clear counter
		HAL_GPIO_WritePin(GPIOD, 0x10 << i, 1);
		HAL_GPIO_WritePin(GPIOD, 0x08 >> i, 1);
		i++;
		if(i > 4)
		{
			i = 0;
			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			if(get_button(BUTTON_0_GPIO_Port, BUTTON_0_Pin, 0) == BUTTON_ACTIVE)
			{
				HAL_GPIO_WritePin(GPIOD, 0xff, 1);
				func_indicator = FLOWER_OFF;
			}
		}
	}
}

void flower_off(void)
{
	static int i = 0;
	if(t1ms_counter > 200)
	{
		t1ms_counter = 0; // clear counter
		HAL_GPIO_WritePin(GPIOD, 0x80 >> i, 0);
		HAL_GPIO_WritePin(GPIOD, 0x01 << i, 0);
		i++;
		if(i > 4)
		{
			i = 0;
			HAL_GPIO_WritePin(GPIOD, 0xff, 1);
			if(get_button(BUTTON_0_GPIO_Port, BUTTON_0_Pin, 0) == BUTTON_ACTIVE)
			{
				HAL_GPIO_WritePin(GPIOD, 0xff, 0);
				func_indicator = LED_KEEP_ON_UP;
			}
		}
	}
}

void led_keep_on_up(void)
{
	static int i = 0;
	if(t1ms_counter > 200)
	{
		t1ms_counter = 0; // clear counter
		HAL_GPIO_WritePin(GPIOD, 0x01 << i, 1);
		i++;
		if(i > 7)
		{
			i = 0;
			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			if(get_button(BUTTON_0_GPIO_Port, BUTTON_0_Pin, 0) == BUTTON_ACTIVE)
			{
				func_indicator = LED_KEEP_ON_DOWN;
			}
		}
	}
}

void led_keep_on_down(void)
{
	static int i = 0;
	if(t1ms_counter > 200)
	{
		if(i == 0)
		{
			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
		}
		t1ms_counter = 0; // clear counter
		HAL_GPIO_WritePin(GPIOD, 0x80 >> i, 1);
		i++;
		if(i > 7)
		{
			i = 0;
			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			if(get_button(BUTTON_0_GPIO_Port, BUTTON_0_Pin, 0) == BUTTON_ACTIVE)
			{
				func_indicator = LED_ON_UP;
			}
		}
	}
}

void led_on_up(void)
{
	static int i = 0;
	if(t1ms_counter > 200)
	{
		HAL_GPIO_WritePin(GPIOD, 0xff, 0);
		t1ms_counter = 0; // clear counter
		HAL_GPIO_WritePin(GPIOD, 0x01 << i, 1);
		i++;
		if(i > 7)
		{
			i = 0;
			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			if(get_button(BUTTON_0_GPIO_Port, BUTTON_0_Pin, 0) == BUTTON_ACTIVE)
			{
				func_indicator = LED_ON_DOWN;
			}
		}
	}
}

void led_on_down(void)
{
	static int i = 0;
	if(t1ms_counter > 200)
	{
		HAL_GPIO_WritePin(GPIOD, 0xff, 0);
		t1ms_counter = 0; // clear counter
		HAL_GPIO_WritePin(GPIOD, 0x80 >> i, 1);
		i++;
		if(i > 7)
		{
			i = 0;
			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			if(get_button(BUTTON_0_GPIO_Port, BUTTON_0_Pin, 0) == BUTTON_ACTIVE)
			{
				func_indicator = LED_ALL_ON;
			}
		}
	}
}

