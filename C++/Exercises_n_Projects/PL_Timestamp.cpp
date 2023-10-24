#pragma once

#include <iostream>
using namespace std;

#include "pl_timestamp.h"

PL_Timestamp::PL_Timestamp()
{
	this->year = 2023;
	this->month = 10;
	this->day = 23;
	this->hour = 16;
	this->minute = 34;
	this->second = 04;
}

PL_Timestamp::PL_Timestamp(int year, int month, int day, int hour, int minute, int second)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

int PL_Timestamp::getYear()
{
	return year;
}

int PL_Timestamp::getMonth()
{
	return month;
}

int PL_Timestamp::getDay()
{
	return day;
}

int PL_Timestamp::getHour()
{
	return hour;
}

int PL_Timestamp::getMinute()
{
	return minute;
}

int PL_Timestamp::getSecond()
{
	return second;
}

void PL_Timestamp::setYear(int year)
{
	this->year = year;
}

void PL_Timestamp::setMonth(int month)
{
	this->month = month;
}

void PL_Timestamp::setDay(int day)
{
	this->day = day;
}

void PL_Timestamp::setHour(int hour)
{
	this->hour = hour;
}

void PL_Timestamp::setMinute(int minute)
{
	this->minute = minute;
}

void PL_Timestamp::setSecond(int second)
{
	this->second = second;
}
