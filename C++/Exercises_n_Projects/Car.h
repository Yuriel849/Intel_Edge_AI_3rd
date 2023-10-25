#pragma once
#ifndef CAR_H
#define CAR_H

#include <string>
#include "PL_Timestamp.h"
using namespace std;

// Car Class는 차량번호, 배차시간, 출차시간, 배차 위치, 장애인차량 유무의 속성을 가지고 있습니다.
class Car
{
private:
	string plate;
	PL_Timestamp arrival;
	PL_Timestamp departure;
	int lot_no;
	int disabled;
public:
	// constructors
	Car();
	Car(string plate, string arrival, string departure, int lot_no, int disabled);
	// getters
	string getPlate();
	int getYear(int ad);
	int getMonth(int ad);
	int getDay(int ad);
	int getHour(int ad);
	int getMinute(int ad);
	int getSecond(int ad);
	int getLotNo();
	int getDisabled();
	// setters
	void setPlate(string plate);
	void setYear(int ad, int year);
	void setMonth(int ad, int month);
	void setDay(int ad, int day);
	void setHour(int ad, int hour);
	void setMinute(int ad, int minute);
	void setSecond(int ad, int second);
	void setLotNo(int lot);
	void setDisabled(int level);
private:
	PL_Timestamp convertDoubleToTimestamp(string datetime);
};
#endif