#ifndef _STEPMOTOR_H_
#define _STEPMOTOR_H_

#include "main.h" // 버튼 조작에 필요한 HAL_Driver나 GPIO 정보가 모두 main.h에 있음
#include "button.h"
#include "timer_management.h"


void do_demo(void);
void kenGwon_test(int direction);

void stepmotor_drive(int step);
void set_RPM(int rpm);
void stepmotor_main_test(void);



#endif /*_STEPMOTOR_H_*/
