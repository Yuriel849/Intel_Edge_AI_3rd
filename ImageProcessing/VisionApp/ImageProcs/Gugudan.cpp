#include <iostream>

int main()
{
	//Quize
	//if...for...
	//GuGuDan
	// input  : dan_start, end(2~9)
	// intput : step_start, end(1~9)

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

	return 1;
}