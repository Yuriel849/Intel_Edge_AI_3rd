/*
 * �������� �ý����� ����ٰ� �������� �� ���� ���� Ŭ������ ����� �����ϰ� ������ϰ� ��������� ����ϴ� �Լ��� c++�� �ۼ��Ͻÿ�.
	- Car Class�� ������ȣ, �����ð�, �����ð�, ���� ��ġ, ��������� ������ �Ӽ��� ������ �ֽ��ϴ�.
	- ���� ����� 1�ð��� 2000�� 30�п� 1000���̸� 10�� ���� ��� �� 400���Դϴ�. (10�й̸� ���� 400��)
 */

#include <iostream>
using namespace std;

#include "car.h"

#if 0
int main()
{
	cout << "Welcome to our parking lot XXX (Lot No. 0123)" << endl;
	cout << "The fees are 2000 KRW per hour, 1000 KRW per 30 minutes, and 400 KRW per 10 minutes. \nThe minimum fee is 400 KRW, even for a stay of less than ten minutes." << endl;

	Car car1("ABCD1234", 20231023165016, 20231023163404, 4, 0);
	int fee = car1.getTimeDifference();
	cout << fee << " should be exactly 400" << endl;

	return 0;
}
#endif