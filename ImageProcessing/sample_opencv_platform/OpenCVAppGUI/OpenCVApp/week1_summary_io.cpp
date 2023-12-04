#include <stdio.h>
#include <iostream>

//#define _CRT_SECURE_NO_WARNINGS
//istream vs ostream
//cin ">>"   cout "<<" 



//#include "abc.h" user defined header file
//함수 형태
//[반환형] [함수명][(매개변수)] {   }


int main()
{
	//출력
	printf("Hello, ");
	printf("World\n");
	std::cout << "Hello, ";
	std::cout << "World\n";
	std::cout << "Hello, World" << std::endl;
	//정수
	printf("math - %d\n", 100);
	std::cout << "math - " << 100 << std::endl;
	//소수
	printf("pi - %lf\n", 3.14);
	std::cout << "pi - " << 3.14 << std::endl;
	//문자
	printf("Score - %c\n", 'A');
	std::cout << "Score - " << 'A' << std::endl;

	printf("%d %lf %c", 100, 3.14, 'A');

	//입력
	//c
	int i = 0;
	scanf("input-%d", &i);//★★★★★
	printf("%d typed", i);

	//c++
	std::cout << "input - "; 
	std::cin >> i;//★★★★★
	std::cout << i << " typed" << std::endl;

	return 1;//TRUE - 1, FALSE - 0
}