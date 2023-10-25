#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "car.h"

Car::Car()
{
	this->plate = "DEFAULT 0123";
	this->lot_no = 0123;
	this->disabled = 0;
}

Car::Car(string plate, string arrival, string departure, int lot_no, int disabled)
{
	this->plate = plate;
	this->arrival = convertDoubleToTimestamp(arrival);
	this->departure = convertDoubleToTimestamp(departure);
	this->lot_no = lot_no;
	this->disabled = disabled;
}

// getters
string Car::getPlate()
{
	return this->plate;
}

int Car::getYear(int ad)
{
	if (ad) // ad == 1이면 arrival
	{
		return this->arrival.getYear();
	}
	else // ad == 0이면 departure
	{
		return this->departure.getYear();
	}
}

int Car::getMonth(int ad)
{
	if (ad) // ad == 1이면 arrival
	{
		return this->arrival.getMonth();
	}
	else // ad == 0이면 departure
	{
		return this->departure.getMonth();
	}
}

int Car::getDay(int ad)
{
	if (ad) // ad == 1이면 arrival
	{
		return this->arrival.getDay();
	}
	else // ad == 0이면 departure
	{
		return this->departure.getDay();
	}
}

int Car::getHour(int ad)
{
	if (ad) // ad == 1이면 arrival
	{
		return this->arrival.getHour();
	}
	else // ad == 0이면 departure
	{
		return this->departure.getHour();
	}
}

int Car::getMinute(int ad)
{
	if (ad) // ad == 1이면 arrival
	{
		return this->arrival.getMinute();
	}
	else // ad == 0이면 departure
	{
		return this->departure.getMinute();
	}
}

int Car::getSecond(int ad)
{
	if (ad) // ad == 1이면 arrival
	{
		return this->arrival.getSecond();
	}
	else // ad == 0이면 departure
	{
		return this->departure.getSecond();
	}
}

int Car::getLotNo()
{
	return this->lot_no;
}

int Car::getDisabled()
{
	return this->disabled;
}

// setters
void Car::setPlate(string plate)
{
	this->plate = plate;
}

void Car::setYear(int ad, int year)
{
	if (ad) // ad == 1이면 arrival
	{
		this->arrival.setYear(year);
	}
	else // ad == 0이면 departure
	{
		this->departure.setYear(year);
	}
}

void Car::setMonth(int ad, int month)
{
	if (ad) // ad == 1이면 arrival
	{
		this->arrival.setMonth(month);
	}
	else // ad == 0이면 departure
	{
		this->departure.setMonth(month);
	}
}

void Car::setDay(int ad, int day)
{
	if (ad) // ad == 1이면 arrival
	{
		this->arrival.setDay(day);
	}
	else // ad == 0이면 departure
	{
		this->departure.setDay(day);
	}
}

void Car::setHour(int ad, int hour)
{
	if (ad) // ad == 1이면 arrival
	{
		this->arrival.setHour(hour);
	}
	else // ad == 0이면 departure
	{
		this->departure.setHour(hour);
	}
}

void Car::setMinute(int ad, int minute)
{
	if (ad) // ad == 1이면 arrival
	{
		this->arrival.setMinute(minute);
	}
	else // ad == 0이면 departure
	{
		this->departure.setMinute(minute);
	}
}

void Car::setSecond(int ad, int second)
{
	if (ad) // ad == 1이면 arrival
	{
		this->arrival.setSecond(second);
	}
	else // ad == 0이면 departure
	{
		this->departure.setSecond(second);
	}
}

void Car::setLotNo(int lot)
{
	this->lot_no = lot;
}

void Car::setDisabled(int level)
{
	this->disabled = level;
}

PL_Timestamp Car::convertDoubleToTimestamp(string datetime)
{
	// "datetime" format -> YYYYMMDDHHMMSS, ex) 20231023163404 for 16 hours 34 minutes 04 seconds on 23 October 2023
	PL_Timestamp timestamp(stoi(datetime.substr(0, 4)), stoi(datetime.substr(4, 2)), stoi(datetime.substr(6, 2)),
		stoi(datetime.substr(8, 2)), stoi(datetime.substr(10, 2)), stoi(datetime.substr(12, 2)));

	return timestamp;
}

#if 0
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
#endif