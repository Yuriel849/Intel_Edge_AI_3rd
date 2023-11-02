#include <iostream>
#include <string>

#include "Gugudan.h"

Gugudan::Gugudan()
	: DanS(2)
	, DanE(9)
	, StepS(1)
	, StepE(9)
{
	std::cout << "Gugudan::Ctor" << std::endl;
}

Gugudan::~Gugudan()
{
	std::cout << "Gugudan::Dtor" << std::endl;
}

void Gugudan::SetParams()
{
	std::cout << "구구단을 출력하려고 최소값과 최대값을 입력해주세요." << std::endl;
	std::cout << "먼저 행의 최소값과 최대값을 입력해주세요 >> ";
	std::cin >> StepS >> StepE;
	std::cout << "다음은 열의 최소값과 최대값을 입력해주세요 >> ";
	std::cin >> DanS >> DanE;
	std::cout << "행은 " << StepS << "부터 " << StepE << "까지, 열은 " << DanS << "부터 " << DanE << "까지로 입력하셨습니다." << std::endl;
}

void Gugudan::Proc()
{
	for (size_t step = this->StepS; step <= this->StepE; step++)
	{
		for (size_t dan = this->DanS; dan <= this->DanE; dan++)
		{
			size_t result = dan * step;
			std::string str = "";
			str = std::to_string(dan);
			str += "*";
			str += std::to_string(step);
			str += "=";
			str += std::to_string(result);
			msg += str + "\t";
		}
		msg += "\n";
	}
}

void Gugudan::Display()
{
	std::cout << msg << std::endl;
}
