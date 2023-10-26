/*
 * 주차관리 시스템을 만든다고 가정했을 때 차에 대한 클래스를 만들어 구현하고 주차등록과 주차요금을 계산하는 함수를 c++로 작성하시오.
	- Car Class는 차량번호, 배차시간, 출차시간, 배차 위치, 장애인차량 유무의 속성을 가지고 있습니다.
	- 주차 요금은 1시간당 2000원 30분에 1000원이며 10분 단위 계산 시 400원입니다. (10분미만 또한 400원)
	- 출차시간과 배차시간은 같은 해, 같은 달 안에 있다고 가정한다. 즉, 출차시간과 배차시간의 시간차는 아무리 높아도 1개월을 넘어가지 않는다.
 */

#include <iostream>
using namespace std;

#include "car.h"

int calculateFee(Car car);

#if 1
int main()
{
	cout << "Welcome to our parking lot XXX (Lot No. 0123)" << endl;
	cout << "The fees are 2000 KRW per hour, 1000 KRW per 30 minutes, and 400 KRW per 10 minutes. \nThe minimum fee is 400 KRW, even for a stay of less than ten minutes." << endl;

	//Car car1("ABCD1234", "20231023163404", "20231025145019", 0123, 0);

	Car car1("ABCD1234", "20231023163404", "20231023170019", 0123, 1);
	cout << "Your car arrived at " << car1.getHour(1) << " hours " << car1.getMinute(1) << " minutes " << car1.getSecond(1) << " seconds on "
		<< car1.getYear(1) << "." << car1.getMonth(1) << "." << car1.getDay(1) << "." << endl;
	cout << "Your car departed at " << car1.getHour(0) << " hours " << car1.getMinute(0) << " minutes " << car1.getSecond(0) << " seconds on "
		<< car1.getYear(0) << "." << car1.getMonth(0) << "." << car1.getDay(0) << "." << endl;
	cout << "Your fee should be exactly " << calculateFee(car1) << " KRW." << endl;
	// int fee = car1.getTimeDifference();
	//cout << fee << " should be exactly 400" << endl;

	return 0;
}
#endif

int calculateFee(Car car)
{
	int fee = 0;
	int minutes = 0;
	int difference = car.getDay(0) - car.getDay(1);
	if (difference != 0)
	{
		minutes += difference * 24 * 60; // Difference in days added as minutes
	}
	difference = car.getHour(0) - car.getHour(1);
	if (abs(difference) > 0)
	{
		if (difference < 0) // ex) departure at 09 hours and arrival at 16 hours, difference = -7
		{
			difference += 24;
			minutes -= 24 * 60;
		}
		minutes += difference * 60; // Difference in hours added as minutes
	}
	difference = car.getMinute(0) - car.getMinute(1);
	if (abs(difference) > 0)
	{
		if (difference < 0) // ex) departure at 15 minutes and arrival at 30 minutes, difference = -15
		{
			difference += 60;
			minutes -= 60;
		}

		minutes += difference; // Difference in minutes added
	}

	// Calculate fee based on the lenght of stay at this parking lot.
	if (minutes > 60) // If stay is longer than one hour
	{
		// The fees are 2000 KRW per hour, 1000 KRW per 30 minutes, and 400 KRW per 10 minutes. \nThe minimum fee is 400 KRW, even for a stay of less than ten minutes

		fee += (minutes / 60) * 2000;
		minutes = minutes % 60;
	}
	else if(minutes >= 30) // If stay is longer than 30 minutes but less than one hour (60 minutes)
	{
		fee += (minutes / 30) * 1000;
		minutes = minutes % 30;
	}
	else if(minutes >= 10) // If stay is longer than 10 minutes but less than 30 minutes
	{
		fee += (minutes / 10) * 400;
	}
	else // If stay is less than 10 minutes
	{
		fee = 400;
	}

	if (car.getDisabled() == 1)
	{
		fee *= 0.5;
	}

	return fee;
}