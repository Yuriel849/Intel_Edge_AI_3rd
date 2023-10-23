#include "main.h" // HAL Driver, GPIO 등 정보가 전부 이 헤더파일에 위치

#define BUTTON_RELEASE 1 // 버튼을 누르지 않은 상태 == 1 (Pull-up 때문에)
#define BUTTON_ACTIVE 0  // 버튼을 누른 상태 == 0(Active-low)
#define BUTTON_NUMBER 4  // 버튼 개수 : 4개

int get_button(GPIO_TypeDef* GPIO, uint16_t GPIO_PIN, uint8_t button_number);
