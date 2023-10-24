#pragma once
#ifndef CAR_H
#define CAR_H

#include <string>
using namespace std;

class Car
{
	// Car Class는 차량번호, 배차시간, 출차시간, 배차 위치, 장애인차량 유무의 속성을 가지고 있습니다.
private:
	string plate;
	double timestamp_arrival;
	double timestamp_departure;
	int lot_no;
	int disabled;
public:
	Car(string plate, double arrival, double departure, int lot_no, int disabled);

	int getTimeDifference();
};
#endif