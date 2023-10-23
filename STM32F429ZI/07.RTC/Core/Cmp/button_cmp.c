//#include "button.h"
//#include "i2c_lcd.h"
//// 초기 버튼 상태 table이 필요하다.
//char button_status[BUTTON_NUMBER] =
//{BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE}; // 버튼 4개가 초기 상태가 끔. 버튼.h에서 개수 갱신하고 여기서 BUTTON_RELEASE 추가/
//uint8_t lcd_display_mode_flag = 0;   // 0 -> time display , 1 -> ````
//
//extern RTC_HandleTypeDef hrtc;
//RTC_TimeTypeDef mTime;  // time info
//
//void lcd_display_mode_select(void)
//{
//	char lcd_buff[40];
//
//	if(get_button(GPIOC, GPIO_PIN_13, 4) == BUTTON_PRESS)
//	{
//		lcd_command(CLEAR_DISPLAY);
//		lcd_display_mode_flag++;
//		lcd_display_mode_flag %= 4;
//		if(lcd_display_mode_flag == 3)
//		{
//			HAL_RTC_GetTime(&hrtc, &mTime, RTC_FORMAT_BCD);
//			sprintf(lcd_buff, "TIME: %02d:%02d:%02d",
//					bin2dec(mTime.Hours), bin2dec(mTime.Minutes), bin2dec(mTime.Seconds));
//			move_cursor(1,0);
//			lcd_string(lcd_buff);
//			move_cursor(1,6); // 시간 정보 field로 커서 이동
//		}
//
//	}
//}
//// get_button(gpio, pin번호, button번호)
//// 완전히 눌렀다 떼면 BUTTON_RELEASE(1) 을 return
//int get_button(GPIO_TypeDef *GPIO, uint16_t GPIO_PIN, uint8_t button_number) // 노이즈 : 안 뗐는데 잠시 뗀 것처럼 나오는 상태 - 디바운스 오브 채터링 / 상태 체크를 해봐야 한다.
//{
//	unsigned char curr_state;
//
//	curr_state = HAL_GPIO_ReadPin(GPIO, GPIO_PIN); // 0, 1
//	// 버튼이 눌려졌으나 처음 상태
//	if (curr_state == BUTTON_PRESS && button_status[button_number] == BUTTON_RELEASE)
//	{
//		HAL_Delay(80); // noise가 지나가기를 기다린다. 80ms 정도면 지나간다.
//		button_status[button_number] = BUTTON_PRESS;  // 현재의 버튼 상태를 저장
//		return BUTTON_RELEASE; // 버튼이 눌려진 상태이나 아직은 noise 상태로 인정.
//	}
//	else if (curr_state == BUTTON_RELEASE && button_status[button_number] == BUTTON_PRESS)
//	{
//		// 1. 이전에 버튼이 눌려진 상태였고 지금은 버튼을 뗀 상태이면
//		button_status[button_number] = BUTTON_RELEASE;  // 2. button_status table을 초기화 하고
//		HAL_Delay(30);
//		return BUTTON_PRESS;  // 3. 버튼을 1번 눌렀다 뗀 것으로 인정한다.
//	}
//	return BUTTON_RELEASE;
//}
