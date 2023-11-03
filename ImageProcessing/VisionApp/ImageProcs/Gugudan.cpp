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
	std::cout << "�������� ����Ϸ��� �ּҰ��� �ִ밪�� �Է����ּ���." << std::endl;
	std::cout << "���� ���� �ּҰ��� �ִ밪�� �Է����ּ��� >> ";
	std::cin >> StepS >> StepE;
	std::cout << "������ ���� �ּҰ��� �ִ밪�� �Է����ּ��� >> ";
	std::cin >> DanS >> DanE;
	std::cout << "���� " << StepS << "���� " << StepE << "����, ���� " << DanS << "���� " << DanE << "������ �Է��ϼ̽��ϴ�." << std::endl;
}

void Gugudan::Proc()
{
	vMsg.clear(); // ���� �ʱ�ȭ

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
		//msg += "\n";
		vMsg.push_back(msg);
	}
}

void Gugudan::Display()
{
	//std::cout << msg << std::endl;

	std::cout << "GuGuDan::Display" << std::endl;
	//for basic
	for (size_t i = 0; i < vMsg.size(); i++)
	{
		std::cout << vMsg[i] << std::endl;
	}
}