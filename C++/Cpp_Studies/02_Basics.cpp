/*
 * Created: 2023.10.23 (MONDAY)
 */

#include <iostream>
 // iostream 헤더 파일
 //     cout, cin, << & >> 연산자 포함!
 //		ios, istream, ostream, iostream 클래스도 선언
 //		iostrean 같은 표준 헤더 파일은 ".h"를 생략

#include "Circle.h"

#if 0
int main()
{
	Circle donut;
	double area = donut.getArea();
	std::cout << " donut의 면적은 " << area << "\n";

	Circle pizza(3);
	area = pizza.getArea();
	std::cout << " pizza의 면적은 " << area << std::endl;

	return 0; // 개발자 편의를 위해 생략 가능, 문제 없음
}
#elif 0
int main()
{
	std::cout<< "입력할 정싀 개수는 ? ";
	int n;
	std::cin >> n; // 정수의 개수 입력
	if(n <= 0) return 0;
	int* p = new int[n];
	if (!p)
	{
		std::cout << "메모리를 할당할 수 없습니다.";
		return 0;
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << i + 1 << "번째 정수: ";
		std::cin >> p[i];
	}

	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += p[i];
	}
	std::cout << "평균 = " << sum / n << std::endl;

	delete[] p;
}
#elif 1
int main()
{
	return 0;
}
#endif