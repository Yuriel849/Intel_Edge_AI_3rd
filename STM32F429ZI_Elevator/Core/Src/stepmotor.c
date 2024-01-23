#include "stepmotor.h"

/*
 * RPM(Revolution Per Minutes): 분당 회전수
 * 1분: 60sec: 1,000,000us(1초) x 60 = 60,000,000us
 *
 * 1,000,000us(초)
 * ==> 1초(1000ms) ==> 1ms(1000us) x 1000ms ==> 1,000,000us
 *
 * 4096 step = 1바퀴
 * 스텝모터에 자력을 줘서 8번 자력의 형상이 바뀌는 것을 sequence 라고 한다.
 * 1 sequence = 8 step : 0.70312도
 * 4096 / 8 ==> 512 sequence : 360도(= 0.70312 x 512)
 */

void stepmotor_main_test(void);

void do_demo(void)
{
	int current_direction = 0;

	while (1)
	{
		if (get_button(BTN0_GPIO_Port, BTN0_Pin, 0) == BUTTON_PRESS)
		{
			if (current_direction == 1) current_direction = 2;
			else if (current_direction == 2) current_direction = 1;
			else current_direction = 1;
		}
		else if (get_button(BTN1_GPIO_Port, BTN1_Pin, 1) == BUTTON_PRESS)
		{
			current_direction = 0;
		}

		kenGwon_test(current_direction);
	}
}


// direction: 1 => 시계방향 회전
//            2 => 반시계방향 회전
//            0 => IDLE
void kenGwon_test(int direction)
{
	static int kenGwon_step = 0;

	if (direction == 1)
	{
		kenGwon_step++;
		if (kenGwon_step >= 8) kenGwon_step = 0;
		kenGwon_step %= 8;
	}
	else if (direction == 2)
	{
		kenGwon_step--;
		if (kenGwon_step < 0) kenGwon_step = 7;
		kenGwon_step %= 8;
	}
	else if (direction == 0)
	{
		kenGwon_step = -1;
	}

	stepmotor_drive(kenGwon_step);
	if (direction == 1) set_RPM(13);
	else if (direction == 2) set_RPM(10);
}


void stepmotor_drive(int step)
{
	switch (step)
	{
		case 0:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
		case 5:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_SET);
			break;
		case 6:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_SET);
			break;
		case 7:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_SET);
			break;
		default:
			HAL_GPIO_WritePin(StepMotor_IN1_GPIO_Port, StepMotor_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN2_GPIO_Port, StepMotor_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN3_GPIO_Port, StepMotor_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMotor_IN4_GPIO_Port, StepMotor_IN4_Pin, GPIO_PIN_RESET);
			break;
	}
}

/*
 * -------- set_RPM(13)으로 지정 시 동작상황 --------
 * 60,000,000us(1분) / 4096step / RPM
 * 1126us(1step IDLE time) x 4096 = 4,612,096us : : 한바퀴 도는데 걸리는 시간
 *                                = 4612ms
 *                                = 4.6초
 * 60초 / 4.6 = 13회전 : 1분동안 돌 수 있는 회전 수
 */
void set_RPM(int rpm) // 가능한 RPM 범위: 1~13
{
	 delay_us(60000000/4096/rpm);
	// 최대 speed 기준(분당 13회전): delay_us(1126);
}

// 시계방향으로 1회전 <---무한반복---> 반시계 방향으로 1회전
void stepmotor_main_test(void)
{
	while(1)
	{
		// 정회전
		for (int sequence = 0; sequence < 2048; sequence++)
		{
			for (int step = 0; step < 8; step++)
			{
				stepmotor_drive(step);
				set_RPM(13);
			}
		}

		// 역회전
		for (int sequence = 0; sequence < 2048; sequence++)
		{
			for (int step = 7; step >= 0; step--)
			{
				stepmotor_drive(step);
				 set_RPM(13);
			}
		}
	}
}




