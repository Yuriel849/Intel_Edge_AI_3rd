#pragma once

#include <iostream>
using namespace std;

#include "car.h"

Car::Car(string plate, double arrival, double departure, int lot_no, int disabled)
{
	this->plate = plate;
	this->timestamp_arrival = arrival;
	this->timestamp_departure = departure;
	this->lot_no = lot_no;
	this->disabled = disabled;
}

// timestamp_arrival/timestamp_depature format YYYYMMDDHHMMSS, ex) 20231023163404 for 16 hours 34 minutes 04 seconds on 23 October 2023
int Car::getTimeDifference()
{
	//-주차 요금은 1시간당 2000원 30분에 1000원이며 10분 단위 계산 시 400원입니다. (10분미만 또한 400원)
	double difference = timestamp_departure - timestamp_arrival;
	int fee = 0;
	if (difference < 1000)
	{
		fee = 400;
	}
	else if (difference <= 3000) // 30분 미만일 경우
	{
		fee = (difference / 1000) * 400;
	}
	else if (difference < 10000)
	{
		fee = 1000 + ((difference - 3000) / 1000 * 400);
	}
	else if (10000 <= difference)
	{
		fee = (difference / 10000 * 2000) + (((difference - 10000) / 3000) * 1000) + ((difference - 10000 - 3000) / 1000 * 400);
	}
	return fee;
}
