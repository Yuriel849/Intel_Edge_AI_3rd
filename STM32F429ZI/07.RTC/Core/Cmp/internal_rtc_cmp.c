//#include "main.h"    // for GPIO & HAL
//#include "i2c_lcd.h"
//#include "button.h"
//
//#include <stdio.h>
//#include <string.h>
//
//void get_rtc(void);
//void set_rtc(char *date_time);
//
//extern RTC_HandleTypeDef hrtc;
//extern uint8_t lcd_display_mode_flag;
//extern RTC_TimeTypeDef mTime;  // time info
//void set_time_button_ui(void);
//
//RTC_TimeTypeDef sTime = {0}; // time info
//RTC_DateTypeDef sDate = {0}; // date info
//
//// 예) 23년이 save된 binary format
//// 7654 3210
//// 0010 0011
//// STM32의 RTC로부터 날짜 & 시각 정보를 읽어 오는 함수
//unsigned char bin2dec(unsigned char byte)    // 이거를 이거로
//{
//	unsigned char high, low;
//	low = byte & 0x0f; // 하위 4bit (low nibble)
//	high = (byte >> 4) * 10; // 상위 4bit (high nibble)
//
//	return high + low;
//
//}
////decimal --> BCD       ex) 23: 0010 0011 /  001 0111?
//unsigned char dec2bin(unsigned char byte)
//{
//	unsigned char high, low;
//
//	high = (byte / 10) << 4;
//	low = byte % 10;
//
//	return high + low;
//}
//void get_rtc(void)
//{
//	static RTC_TimeTypeDef oldTime; // 구조체, 이전 시각 정보를 가지고 있기 위함이다. // 리셋되지 않고 그대로 유지. 스태틱 전역 변수
//	char lcd_buff[40];
//	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
//	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
//
//	if (oldTime.Seconds != sTime.Seconds) // 시간이 달라지면
//	{
//		// YYYY-MM-DD HH:MM:ss
//		printf("%04d-%02d-%02d %02d:%02d:%02d\n", bin2dec(sDate.Year)+2000, bin2dec(sDate.Month), bin2dec(sDate.Date),
//				bin2dec(sTime.Hours), bin2dec(sTime.Minutes), bin2dec(sTime.Seconds));   // 2 -> 10
//
//		if (lcd_display_mode_flag == 0)
//		{
//			sprintf(lcd_buff, "DATE: %04d-%02d-%02d ",
//					bin2dec(sDate.Year)+2000, bin2dec(sDate.Month), bin2dec(sDate.Date));
//			move_cursor(0,0);
//			lcd_string(lcd_buff);
//// \n은 찌꺼기 값
//			sprintf(lcd_buff, "TIME: %02d:%02d:%02d",
//					bin2dec(sTime.Hours), bin2dec(sTime.Minutes), bin2dec(sTime.Seconds));
//			move_cursor(1,0);
//			lcd_string(lcd_buff);
//		}
//
//	}
//	oldTime.Seconds = sTime.Seconds;  // 현재 시간을 올드 타임으로 만들어준다.
//} // 시간이 틀어져서 시간을 보정하려고 한다.
//
//
//// setrtc231016103800
//// 012345678901234567 방
//void set_rtc(char *date_time)
//{
//	char yy[4], mm[4], dd[4];   // date
//	char hh[4], min[4], ss[4];  // time
//
//	strncpy(yy, date_time+6, 2); // yy[0] = '2', yy[1] = '3',yy[2] = '0' 널;
//	strncpy(mm, date_time+8, 2);
//	strncpy(dd, date_time+10, 2);
//
//	strncpy(hh, date_time+12, 2);
//	strncpy(min, date_time+14, 2);
//	strncpy(ss, date_time+16, 2);
//
//	// ascii --> int --> bcd
//	sDate.Year = dec2bin(atoi(yy));
//	sDate.Month = dec2bin(atoi(mm));
//	sDate.Date = dec2bin(atoi(dd));
//
//	sTime.Hours = dec2bin(atoi(hh));
//	sTime.Minutes = dec2bin(atoi(min));
//	sTime.Seconds = dec2bin(atoi(ss));
//
//	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
//	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
//}
//
//// button0 : 시간 정보를 변경 버튼. 00~23시 (up counter)
//// buttom1 : 분을 변경하는 버튼. 00~59 (up counter)
//// button2 : 초를 변경하는 버튼. 00~59 (up counter)
//// button3 : 변경 완료. 현재까지 변경된 내용을 저장
//// HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
//void set_time_button_ui(void)
//{
//	if(lcd_display_mode_flag == 3)
//	{
//		if (get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
//		{
//			// 시간 정보 modify +1
//		}
//		if (get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)
//		{
//			// 분 정보 modify +1
//		}
//		if (get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)
//		{
//			// 초 정보 modify +1
//		}
//		if (get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS)
//		{
//			HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD); // 누르면 최종적으로 업데이트
//		}
//	}
//}
//// [STM32] BUTTON UI(RTC TIME MODIFY)
//// 1. FSM
//// 2. source
//// 3. 동영상
//
//
//
//
//
//
//
