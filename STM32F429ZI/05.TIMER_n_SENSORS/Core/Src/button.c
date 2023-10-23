#include "button.h" // <>는 라이브러리에 있는 파일을 가져올 때, 현재 디렉터리에 있는 파일을 가져올 때는 "" 사용

char button_status[BUTTON_NUMBER] =
{
		BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE
};

// 완전히 눌렀다가 떼면 BUTTON_RELEASE (값 : 1) 반환
int get_button(GPIO_TypeDef* GPIO, uint16_t GPIO_PIN, uint8_t button_number)
{
	unsigned char curr_state;
	curr_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN); // 반환값 0 or 1

	if(curr_state == BUTTON_ACTIVE && button_status[button_number] == BUTTON_RELEASE)
	{
		HAL_Delay(160); // 노이즈가 지나가기를 기다린다.
		button_status[button_number] = BUTTON_ACTIVE; // 현재의 버튼 상태를 저장
		return BUTTON_RELEASE; // 버튼이 눌려진 상태이나 아직은 노이즈 상태로 인정
	}
	else if (curr_state == BUTTON_RELEASE && button_status[button_number] == BUTTON_ACTIVE)
	{ // 1. 이전에 버튼이 눌려진 상태였으나 지금은 버튼을 뗀 상태라면
		button_status[button_number] = BUTTON_RELEASE; // 2. button_status 테이블 초기화하고
		return BUTTON_ACTIVE; // 3. 버튼을 1번 눌렀다 떼었다고 인정한다
	}
	return BUTTON_RELEASE;
}


