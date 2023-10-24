#pragma once
#ifndef CAR_H
#define CAR_H

#include <string>
using namespace std;

class Car
{
	// Car Class�� ������ȣ, �����ð�, �����ð�, ���� ��ġ, ��������� ������ �Ӽ��� ������ �ֽ��ϴ�.
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