/*
 * Created: 2023.10.23 (MONDAY)
 */

#include <iostream>
 // iostream ��� ����
 //     cout, cin, << & >> ������ ����!
 //		ios, istream, ostream, iostream Ŭ������ ����
 //		iostrean ���� ǥ�� ��� ������ ".h"�� ����

#include "Circle.h"

#if 0
int main()
{
	Circle donut;
	double area = donut.getArea();
	std::cout << " donut�� ������ " << area << "\n";

	Circle pizza(3);
	area = pizza.getArea();
	std::cout << " pizza�� ������ " << area << std::endl;

	return 0; // ������ ���Ǹ� ���� ���� ����, ���� ����
}
#elif 0
int main()
{
	std::cout<< "�Է��� ���� ������ ? ";
	int n;
	std::cin >> n; // ������ ���� �Է�
	if(n <= 0) return 0;
	int* p = new int[n];
	if (!p)
	{
		std::cout << "�޸𸮸� �Ҵ��� �� �����ϴ�.";
		return 0;
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << i + 1 << "��° ����: ";
		std::cin >> p[i];
	}

	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += p[i];
	}
	std::cout << "��� = " << sum / n << std::endl;

	delete[] p;
}
#elif 1
int main()
{
	return 0;
}
#endif