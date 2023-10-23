#if 0
#include "uart.h"
#include <string.h> // strncmp, strcpy...

void pc_command_processing(void);

extern uint8_t rx_data;	// uart3 rx data
extern UART_HandleTypeDef huart3;

// HW와 SW의 만나는 약속장소 : call back function
// move from HAL_UART_RxCpltCallback of stm32f4xx_hal_uart to here
// UART로 1 byte가 수신되면 HW가 call을 해줌
// UART RX INT가 발생이 되면 이곳으로 자동적으로 들어온다.
// comport master
// ledallon\n
// ledalloff\n
// led_toggle\n
#define COMMAND_LENGTH 40
volatile unsigned char rx_buff[COMMAND_LENGTH]; // UART3으로부터 수신된 char를 저장하는 공간(\n을 만날때까지)
volatile int rx_index=0;						// rx_buff의 save 위치
volatile int newline_detect_flag=0;				// new line을 만났을때의 indicator ex) ledallon\n
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart3) // comport master와 연결된 uart
	{
		if(rx_index < COMMAND_LENGTH) // 현재까지 들어온 byte가 40byte를 넘지 않으면
		{
			if(rx_data == '\n' || rx_data == '\r') // newline or 캐리지리턴
			{
				rx_buff[rx_index] = 0;		// '\0'
				newline_detect_flag = 1; 	// new line을 만났다는 flag를 set함.
				rx_index = 0;				// 다음 message저장을 위해서 rx_index값을 0으로함
			}
			else
			{
				rx_buff[rx_index++] = rx_data;
			}
		}
		else
		{
			rx_index = 0;
			printf("Message Overflow !!!!!\n");
		}
		// 주의: 반드시 HAL_UART_Receive_IT를 call해줘야 다음 INT가 발생된다.
		HAL_UART_Receive_IT(&huart3, &rx_data, 1);
	}
}

void pc_command_processing(void)
{
	if(newline_detect_flag) // comport master로부터 완전한 문장이 들어오면 (\n을 만나면)
	{
		newline_detect_flag = 0;
		printf("%s\n", rx_buff);
		if(!strncmp(rx_buff, "ledallon", strlen("ledallon")))
		{
			HAL_GPIO_WritePin(GPIOD, 0xff, 1);
		}
		if(!strncmp(rx_buff, "ledalloff", strlen("ledalloff")))
		{
			HAL_GPIO_WritePin(GPIOD, 0xff, 0);

		}
	}
}
#endif
