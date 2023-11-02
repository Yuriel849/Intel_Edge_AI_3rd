#include <iostream>
#include <string>

#include "Gugudan.h"

int main()
{
	// 구구단 실습 문제
	// input  : dan_start, end(2~9)
	// output : step_start, end(1~9)

	//dan : 2~9, step : 1~9
	//2*1 = 2      3*1=3    ....     9*1=9
	//2*2 = 4      3*2=6    ....     9*2=18
	//
	//2*9 = 18     3*9=27   ....     9*9=81

	//dan : 2~9, step : 9~9
	//2*9 = 18     3*9=27   ....     9*9=81

	std::cout << "Gugudan" << std::endl;

	int dan_start = 2, dan_end = 9, step_start = 1, step_end = 9;

	if (1 < dan_start && dan_end < 10 && dan_start <= dan_end && 0 < step_start && step_end < 10 && step_start <= step_end)
	{
		int dan_temp = dan_start;
		for (; step_start <= step_end; step_start++)
		{
			for (dan_start = dan_temp; dan_start <= dan_end; dan_start++)
			{
				std::cout << dan_start << "*" << step_start << "=" << dan_start * step_start << "\t";
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;

	// ALTERNATIVE
	int DanS, DanE, StepS, StepE;
	DanS = 2, DanE = 5, StepS = 1, StepE = 9;
	for (size_t step = StepS; step <= StepE; step++)
	{
		std::string msg = "";
		for (size_t dan = DanS; dan <= DanE; dan++)
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
		std::cout << msg << std::endl;
	}
	std::cout << std::endl;

	Gugudan gugudan;
	gugudan.SetParams();
	gugudan.Proc();
	gugudan.Display();

	return 1;
}