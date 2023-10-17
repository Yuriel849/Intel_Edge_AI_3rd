/*
 * washing_machine.c
 *
 *  Created on: Oct 17, 2023
 *      Author: USER
 */

#include "washing_machine.h"
#include "button.h"
#include "i2c_lcd.h"

void run_washing_machine(void);

void run_washing_machine(void)
{
	/* Switch statement for state and description of FSM for this washing machine
		state == 0, idle and doing nothing
			If USER_Btn is pressed, change to state == 1, if state == 0
			BUT if USER_Btn is pressed when if state != 0, change to state == 0 and cancel all changes and actions
		state == 1, mode selection
			Select manual mode or auto mode with BTN1 as "left" and BTN2 as "button", and confirm with BTN0
			If BTN0 is pressed, switch to state == 2 or state == 3, depending on user selection
		state == 2, manual user input mode
			Display on screen and user selects in order the number of washes, rinses, and dryings
			BTN0 to confirm selection, BTN1 as "up" and BTN2 as "down", and BTN3 as "next"
			BTN1 and BTN2 used to increase or decrease number of washes/rinses/dryings (min. 1 ~ max. 5)
			BTN3 used to switch to next selection (after choosing number of dryings, switch back to number of washes)
			If BTN0 is pressed, switch to state == 3 and overwrite wash configuration
		state == 3, run washing (with or without manual user input)
			Preconfigured wash configuration overwritten if coming from state == 2
			state is automatic operation with no user input, except to cancel with USER_Btn and pause/unpause with BTN0
			Ring buzzer when starting and ending state == 3
			Run specific number of wash cycles, then rinse cycles, then dry cycles, before finishing and returning to state == 0

		Necessary src files: I2C_LCD driver, DC_motor driver, Button driver, Buzzer driver
	 */

	static char state = 0;
	static char wash = 2;
	static char rinse = 2;
	static char drying = 3;
	static char user_select = 3;
	static char user_select_flag = 0;

	// Reset
	if(state != 0 && get_button(GPIOC, GPIO_PIN_13, 4) == BUTTON_PRESS)
	{
		state = 0; // reset to IDLE mode
		wash = 2; // reset to default
		rinse = 2; // reset to default
		drying = 3; // reset to default
		user_select = 3; // reset to default
		lcd_command(CLEAR_DISPLAY);
	}

	switch(state)
	{
	case 0: // IDLE state / DO NOTHING
		lcd_command(CLEAR_DISPLAY);
		// If USER_Btn is pressed, change to state == 1
		if(get_button(GPIOC, GPIO_PIN_13, 4) == BUTTON_PRESS)
		{
			state = 1;
		}
		break;
	case 1: // MODE SELECTION state
		// Display user interface
		move_cursor(0,0);
		lcd_string("Select mode : ");

		// Switch between manual and auto mode with BTN2 as "left" and BTN1 as "right"
		if((get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS) || (get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS))
		{
			if(user_select_flag == 0)
			{
				user_select_flag = 1;
				user_select = 2;
			}
			else if (user_select_flag == 1)
			{
				user_select_flag = 0;
				user_select = 3;
			}
		}

		if(user_select_flag == 0)
		{
			move_cursor(1,0);
			lcd_string("<< AUTO MODE >> ");
		}
		else if(user_select_flag == 1)
		{
			move_cursor(1,0);
			lcd_string("<< USER INPUT >>");
		}

		// If BTN0 is pressed, switch to state == 2 or state == 3 (default state = 3)
		if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
		{
			lcd_command(CLEAR_DISPLAY);
			user_select_flag = 0;
			state = user_select;
		}
		break;
	case 2: // MANUAL USER INPUT state
		// Display on screen and user selects in order the number of washes, rinses, and dryings
		// BTN0 to confirm selection, BTN1 as "up" and BTN2 as "down", and BTN3 as "next"
		// BTN1 and BTN2 used to increase or decrease number of washes/rinses/dryings (min. 1 ~ max. 5)
		// BTN3 used to switch to next selection (after choosing number of dryings, switch back to number of washes)
		// If BTN0 is pressed, switch to state == 3 and overwrite wash configuration

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);  // LED2
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);  // LED3


		if(get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)
		{
			user_select = ++user_select % 5;
		}
		if(get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)
		{
			user_select = --user_select % 5;
		}
		else if(get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS)
		{
			user_select_flag = ++user_select_flag % 3;
		}

		move_cursor(0,0);
		lcd_string("Manual input : ");

		if(user_select_flag == 0)
		{
			move_cursor(1,0);
			if(user_select == 1)
			{
				lcd_string("Wash: *1 2345   ");
			}
			else if(user_select == 2)
			{
				lcd_string("Wash: 1 *2 345  ");
			}
			else if(user_select == 2)
			{
				lcd_string("Wash: 12 *3 45  ");
			}
			else if(user_select == 2)
			{
				lcd_string("Wash: 123 *4 5  ");
			}
			else if(user_select == 2)
			{
				lcd_string("Wash: 1234 *5   ");
			}
		}
		else if(user_select_flag == 1)
		{
			move_cursor(1,0);
			if(user_select == 1)
			{
				lcd_string("Rinse: *1 2345  ");
			}
			else if(user_select == 2)
			{
				lcd_string("Rinse: 1 *2 345 ");
			}
			else if(user_select == 2)
			{
				lcd_string("Rinse: 12 *3 45 ");
			}
			else if(user_select == 2)
			{
				lcd_string("Rinse: 123 *4 5 ");
			}
			else if(user_select == 2)
			{
				lcd_string("Rinse: 1234 *5  ");
			}
		}
		else if(user_select_flag == 2)
		{

			move_cursor(1,0);
			if(user_select == 1)
			{
				lcd_string("Dry: *1 2345    ");
			}
			else if(user_select == 2)
			{
				lcd_string("Dry: 1 *2 345   ");
			}
			else if(user_select == 2)
			{
				lcd_string("Dry: 12 *3 45   ");
			}
			else if(user_select == 2)
			{
				lcd_string("Dry: 123 *4 5   ");
			}
			else if(user_select == 2)
			{
				lcd_string("Dry: 1234 *5    ");
			}
		}


		if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
		{
			state = 3;
		}
		break;
	case 3: // RUN WASHING MACHINE state
		// state is automatic operation with no user input, except to cancel with USER_Btn and pause/unpause with BTN0
		// Ring buzzer when starting and ending state == 3
		// Run specific number of wash cycles, then rinse cycles, then dry cycles, before finishing and returning to state == 0

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);  // LED3
		HAL_Delay(500);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);  // LED3
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);  // LED3
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);  // LED3

		// Finish
		HAL_Delay(2000);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);  // LED3
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);  // LED3
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);  // LED3
		break;
	default:
		break;
	}

}
