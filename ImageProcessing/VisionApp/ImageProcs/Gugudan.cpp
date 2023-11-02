#include <iostream>
#include <string>

#include "Gugudan.h"

Gugudan::Gugudan()
	: DanS(2)
	, DanE(9)
	, StepS(1)
	, StepE(9)
{}

void Gugudan::setParams()
{
	std::cout << "�������� ����Ϸ��� �ּҰ��� �ִ밪�� �Է����ּ���." << std::endl;
	std::cout << "���� ���� �ּҰ��� �ִ밪�� �Է����ּ��� >> ";
	std::cin >> StepS >> StepE;
	std::cout << "������ ���� �ּҰ��� �ִ밪�� �Է����ּ��� >> ";
	std::cin >> DanS >> DanE;
	std::cout << "���� " << StepS << "���� " << StepE << "����, ���� " << DanS << "���� " << DanE << "������ �Է��ϼ̽��ϴ�." << std::endl;
}

void Gugudan::proc()
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

void Gugudan::display()
{
	std::cout << msg << std::endl;
}
