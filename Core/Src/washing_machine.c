/*
 * washing_machine.c
 *
 *  Created on: Oct 17, 2023
 *      Author: USER
 */

#include "washing_machine.h"

void run_washing_machine(void);

void run_washing_machine(void)
{
	/* Switch statement for run_state and description of FSM for this washing machine
		run_state == 0, idle and doing nothing
			If USER_Btn is pressed, change to run_state == 1, if run_state == 0
			If USER_Btn is pressed and if run_state != 0, change to run_state == 0 and cancel all changes and actions
		run_state == 1, mode selection
			Select manual mode or auto mode with BTN1 as "up" and BTN2 as "down", and confirm with BTN0
			If BTN0 is pressed, switch to run_state == 2 or run_state == 3, depending on user selection
		run_state == 2, manual user input mode
			Display on screen and user selects in order the number of washes, rinses, and dryings
			BTN0 to confirm selection, BTN1 as "up" and BTN2 as "down", and BTN3 as "next"
			BTN1 and BTN2 used to increase or decrease number of washes/rinses/dryings (min. 1 ~ max. 5)
			BTN3 used to switch to next selection (after choosing number of dryings, switch back to number of washes)
			If BTN0 is pressed, switch to run_state == 3 and overwrite wash configuration
		run_state == 3, run washing (with or without manual user input)
			Preconfigured wash configuration saved in run_state == 3; overwritten if coming from run_state == 2
			run_state is automatic operation with no user input, except to cancel with USER_Btn and pause/unpause with BTN0
			Ring buzzer when starting and ending run_state == 3
			Run specific number of wash cycles, then rinse cycles, then dry cycles, before finishing and returning to run_state == 0
	 */
}
