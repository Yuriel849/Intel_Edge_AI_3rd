#include "uart.h"
#include <string.h>

void pc_command_processing(void);
void bt_command_processing(void);

// main.c에 위치
extern uint8_t rx_data;			  // PC data buffer
extern uint8_t bt_rx_data;		  // BT data buffer
extern UART_HandleTypeDef huart3; // PC
extern UART_HandleTypeDef huart6; // BT

// led_final.c에 위치
extern void led_all_on(void);
extern void led_all_off(void);
extern void led_on_sequential(void);
extern void led_off_sequential(void);
extern void led_on_up(void);
extern void led_on_down(void);
extern void led_keep_on_up(void);
extern void led_keep_on_down(void);
extern void flower_on(void);
extern void flower_off(void);

// HW & SW의 만나는 약속 장소: callback function
// From HAL_UART_RxCpltCallback() in "Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c"
// UART로 1 byte가 수신되면 HW가 자동호출해 준다. UART RX INT가 발생하면 자동으로 이 함수를 호출한다.
//1차원 배열 가지고는 overflow가 발생하므로 2차원 배열 circular queue를 구상하여 overflow가 발생 되지 않도록 구현해야 한다.
/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
#define COMMAND_NUM 20
#define COMMAND_LENGTH 40

#if 1 // circular queue... actually two dimensional array
volatile unsigned char rx_buff[COMMAND_NUM][COMMAND_LENGTH]; // UART3으로부터 수신된 char를 저장하는 공간 (\n 만날때까지)
volatile int newline_detect_flag = 0; 			// new line을 만났을 때의 indicator 예 ) ledallon\n)
volatile int x_idx = 0;
volatile int y_idx = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// 2차원 배열: [X][Y].. each [X] is one line of command with max Y characters
	if(huart == &huart3) // ComPortMaster와 연결된 uart 사용
	{
		if(x_idx < COMMAND_NUM)
		{
			if(y_idx < COMMAND_LENGTH)
			{
				if(rx_data == '\n' || rx_data == '\r')
				{
					rx_buff[x_idx][y_idx+1] = 0; // '\0'
					newline_detect_flag = 1; // new line을 만났다는 flag를 set한다.
					y_idx = 0; // 다음 message 저장을 위해서 y_idx값을 0으로 한다.
					x_idx++; // 다음 command로 넘어간다 (2차원 배열의 첫번째 차원에서 다음으로 이동)
				}
				else
				{
					rx_buff[x_idx][y_idx++] = rx_data;
				}
			}
			else
			{
				y_idx = 0;
			}
		}
		else // COMMAND_NUM을 초과하는 수의 명령을 입력했으면, 다시 처음부터 시작
		{
			x_idx = 0;
			printf("Commands overflow !! Cycling back to start !!\n");
		}
		// 주의: 반드시 HAL_UART_Receive_IT를 call해줘야 다음 INT가 발생된다.
		HAL_UART_Receive_IT(&huart3, &rx_data, 1);
	}
}

void pc_command_processing(void)
{
	if(newline_detect_flag) // ComPortMaster로부터 완전한 문장이 들어오면 (\n을 만나면)
	{
		newline_detect_flag = 0;
		printf("%s\n", rx_buff[x_idx-1]);
		if(!strncmp(rx_buff[x_idx-1], "led_all_on", strlen("led_all_on"))) //
		{
			led_all_on();
			return;
		}
		if(!strncmp(rx_buff[x_idx-1], "led_all_off", strlen("led_all_off"))) //
		{
			led_all_off();
			return;
		}
		if(!strncmp(rx_buff[x_idx-1], "led_on_down", strlen("led_on_down"))) //
		{
			led_on_down();
			return;
		}
		if(!strncmp(rx_buff[x_idx-1], "led_on_up", strlen("led_on_up"))) //
		{
			led_on_up();
			return;
		}
		if(!strncmp(rx_buff[x_idx-1], "flower_on", strlen("flower_on"))) //
		{
			flower_on();
			return;
		}
		if(!strncmp(rx_buff[x_idx-1], "flower_off", strlen("flower_off"))) //
		{
			flower_off();
			return;
		}
		if(!strncmp(rx_buff[x_idx-1], "led_keep_on_up", strlen("led_keep_on_up"))) //
		{
			led_keep_on_up();
			return;
		}
		if(!strncmp(rx_buff[x_idx-1], "led_keep_on_down", strlen("led_keep_on_down"))) //
		{
			led_keep_on_down();
			return;
		}
		printf("NO MATCH!!\n");
	}
}




#else // original without circular queue
volatile unsigned char rx_buff[COMMAND_LENGTH]; // UART3으로부터 수신된 char를 저장하는 공간 (\n 만날때까지)
volatile int rx_index = 0;						// rx_buff의 save위치를 가리킨다.
volatile int newline_detect_flag = 0; 			// new line을 만났을 때의 indicator 예 ) ledallon\n)

volatile unsigned char bt_rx_buff[COMMAND_LENGTH]; // UART6으로부터 수신된 char를 저장하는 공간 (\n 만날때까지)
volatile int bt_rx_index = 0; 					   // rx_buff의 save위치를 가리킨다.
volatile int bt_newline_detect_flag = 0; 		   // new line을 만났을 때의 indicator 예 ) ledallon\n)

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart3) // ComPortMaster와 연결된 uart 하용
	{
		if(rx_index < COMMAND_LENGTH)
		{
			if(rx_data == '\n' || rx_data == '\r')
			{
				rx_buff[rx_index] = 0; // '\n'
				newline_detect_flag = 1; // new line을 만났다는 flag를 set한다.
				rx_index = 0; // 다음 message 저장을 위해서 rx_index값을 0으로 한다.
			}
			else
			{
				rx_buff[rx_index++] = rx_data;
			}
		}
		else
		{
			rx_index = 0;
			printf("Message Overflow !!\n");
		}
		// 주의: 반드시 HAL_UART_Receive_IT를 call해줘야 다음 INT가 발생된다.
		HAL_UART_Receive_IT(&huart3, &rx_data, 1);
	}

	if(huart == &huart6) // ComPortMaster와 연결된 uart 하용
	{
		if(bt_rx_index < COMMAND_LENGTH)
		{
			if(bt_rx_data == '\n' || bt_rx_data == '\r')
			{
				bt_rx_buff[rx_index] = 0; // '\n'
				bt_newline_detect_flag = 1; // new line을 만났다는 flag를 set한다.
				bt_rx_index = 0; // 다음 message 저장을 위해서 rx_index값을 0으로 한다.
			}
			else
			{
				bt_rx_buff[bt_rx_index++] = bt_rx_data;
			}
		}
		else
		{
			bt_rx_index = 0;
			printf("BLUETOOTH Message Overflow !!\n");
		}
		// 주의: 반드시 HAL_UART_Receive_IT를 call해줘야 다음 INT가 발생된다.
		HAL_UART_Receive_IT(&huart6, &bt_rx_data, 1);
	}
}

void pc_command_processing(void)
{
	if(newline_detect_flag) // ComPortMaster로부터 완전한 문장이 들어오면 (\n을 만나면)
	{
		newline_detect_flag = 0;
		printf("%s\n", rx_buff);
		if(!strncmp(rx_buff, "led_all_on", strlen("led_all_on"))) //
		{
//			HAL_GPIO_WritePin(GPIOD, 0xff, 1);
			led_all_on();
			return;
		}
		if(!strncmp(rx_buff, "led_all_off", strlen("led_all_off"))) //
		{
//			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			led_all_off();
			return;
		}
		if(!strncmp(rx_buff, "led_on_down", strlen("led_on_down"))) //
		{
			led_on_down();
			return;
		}
		if(!strncmp(rx_buff, "led_on_up", strlen("led_on_up"))) //
		{
			led_on_up();
			return;
		}
		if(!strncmp(rx_buff, "flower_on", strlen("flower_on"))) //
		{
			flower_on();
			return;
		}
		if(!strncmp(rx_buff, "flower_off", strlen("flower_off"))) //
		{
			flower_off();
			return;
		}
		if(!strncmp(rx_buff, "led_keep_on_up", strlen("led_keep_on_up"))) //
		{
			led_keep_on_up();
			return;
		}
		if(!strncmp(rx_buff, "led_keep_on_down", strlen("led_keep_on_down"))) //
		{
			led_keep_on_down();
			return;
		}
	}
}

void bt_command_processing(void)
{
	if(bt_newline_detect_flag) // ComPortMaster로부터 완전한 문장이 들어오면 (\n을 만나면)
	{
		bt_newline_detect_flag = 0;
		printf("%s\n", bt_rx_buff);
		if(!strncmp(bt_rx_buff, "led_all_on", strlen("led_all_on"))) //
		{
//			HAL_GPIO_WritePin(GPIOD, 0xff, 1);
			led_all_on();
			return;
		}
		if(!strncmp(bt_rx_buff, "led_all_off", strlen("led_all_off"))) //
		{
//			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			led_all_off();
			return;
		}
		if(!strncmp(bt_rx_buff, "led_on_down", strlen("led_on_down"))) //
		{
			led_on_down();
			return;
		}
		if(!strncmp(bt_rx_buff, "led_on_up", strlen("led_on_up"))) //
		{
			led_on_up();
			return;
		}
		if(!strncmp(bt_rx_buff, "flower_on", strlen("flower_on"))) //
		{
			flower_on();
			return;
		}
		if(!strncmp(bt_rx_buff, "flower_off", strlen("flower_off"))) //
		{
			flower_off();
			return;
		}
		if(!strncmp(bt_rx_buff, "led_keep_on_up", strlen("led_keep_on_up"))) //
		{
			led_keep_on_up();
			return;
		}
		if(!strncmp(bt_rx_buff, "led_keep_on_down", strlen("led_keep_on_down"))) //
		{
			led_keep_on_down();
			return;
		}
	}
}
#endif

