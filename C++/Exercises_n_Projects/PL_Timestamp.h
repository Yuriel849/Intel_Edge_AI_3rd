#pragma once
#ifndef PL_TIMESTAMP_H
#define PL_TIMESTAMP_H

#include <string>
using namespace std;

class PL_Timestamp
{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
public:
	PL_Timestamp();
	PL_Timestamp(int year, int month, int day, int hour, int minute, int second);
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
	int getSecond();
	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	void setHour(int hour);
	void setMinute(int minute);
	void setSecond(int second);
};
#endif
