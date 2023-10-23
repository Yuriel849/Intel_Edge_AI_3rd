//#include "ultrasonic.h"
//
//extern volatile int TIM10_10ms_ultrasonic; //이중 선언 방지로 초기값 없음.
//void ultrasonic_processing(void);
//
//
//volatile int distance;  // 거리를 측정한 펄스 개수를 저장하는 변수
//volatile int ic_cpt_finish_flag = 0; // 초음파 거리 측정 완료 indicator 변수
//// 1. Drivers/STM32F4xx_HALL_Driver/Src/stm32f4xx_hal_tim.c에 가서
//// HAL_TIM_IC_CaptureCallback을 잘라내기를 해서 이곳으로 가져 온다.
//// 2. 초음파 센서의 ECHO핀의 상승 에지와 하강 에지 발생 시 이곳으로 들어온다.
//volatile uint8_t is_first_capture = 0; // 0: 상승 에지 1: 하강 에지
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//	if (htim->Instance == TIM3)
//	{
//		if (is_first_capture == 0)   // 상승에지
//		{
//			__HAL_TIM_SET_COUNTER(htim, 0); // clear H/W counter
//			is_first_capture = 1;	// 상승 에지를 만났다는 flag변수 indicator를 set
//		}
//		else if (is_first_capture == 1)	// 하강 에지를 만나면
//		{
//			is_first_capture = 0;  // 다음 echo 펄스를 count 하기 위해 변수 초기화
//			distance = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // 현재까지 count한 펄스 수를 읽어 온다.
//			ic_cpt_finish_flag = 1; // 초음파 측정 완료
//		}
//	}
//}
//
//void ultrasonic_processing(void)
//{
//	int dis;  // 거리를 측정한 펄스 개수를 저장하는 변수
//
//	if (TIM10_10ms_ultrasonic >= 100)    // 1초
//	{
//		TIM10_10ms_ultrasonic = 0;
//		make_trigger();
//		if (ic_cpt_finish_flag)   // 초음파 측정이 완료되었으면 - if (ic_cpt_finish_flag) >= 1
//		{
//			ic_cpt_finish_flag = 0;
//			dis = distance;
//			dis = dis * 0.034 / 2; // 1us가 0.034cm를 이동
//			// 왕복 거리를 리턴해 주기 때문에 /2를 해주는 것이다.
//			printf("dis: %dcm\n", dis);
//		}
//	}
//}
//void make_trigger()
//{
//	HAL_GPIO_WritePin(ULTRASONIC_TRIGGER_GPIO_Port, ULTRASONIC_TRIGGER_Pin, 0);  // 일단 0부터 시작
//	delay_us(2);
//	HAL_GPIO_WritePin(ULTRASONIC_TRIGGER_GPIO_Port, ULTRASONIC_TRIGGER_Pin, 1);
//	delay_us(10);
//	HAL_GPIO_WritePin(ULTRASONIC_TRIGGER_GPIO_Port, ULTRASONIC_TRIGGER_Pin, 0);
//}
//
//
//
