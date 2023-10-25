/*
 * 주차관리 시스템을 만든다고 가정했을 때 차에 대한 클래스를 만들어 구현하고 주차등록과 주차요금을 계산하는 함수를 c++로 작성하시오.
	- Car Class는 차량번호, 배차시간, 출차시간, 배차 위치, 장애인차량 유무의 속성을 가지고 있습니다.
	- 주차 요금은 1시간당 2000원 30분에 1000원이며 10분 단위 계산 시 400원입니다. (10분미만 또한 400원)
 */

#include <iostream>
using namespace std;

#include "car.h"

#if 1
int main()
{
	cout << "Welcome to our parking lot XXX (Lot No. 0123)" << endl;
	cout << "The fees are 2000 KRW per hour, 1000 KRW per 30 minutes, and 400 KRW per 10 minutes. \nThe minimum fee is 400 KRW, even for a stay of less than ten minutes." << endl;

	Car car1("ABCD1234", "20231023163404", "20231025145019", 0123, 0);
	cout << "Your car departed at " << car1.getHour(0) << " hours " << car1.getMinute(0) << " minutes " << car1.getSecond(0) << " seconds on "
		<< car1.getYear(0) << "." << car1.getMonth(0) << "." << car1.getDay(0) << "." << endl;
	// int fee = car1.getTimeDifference();
	//cout << fee << " should be exactly 400" << endl;

	return 0;
}
#endif