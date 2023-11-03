#include <iostream>
#include <map>

#if 1
int main()
{
	/* 가장 많은/적은 빈도수의 값을 출력하시오.
	 * 예상 답변
	 *		가장 많은 빈도 값: 4 ... 3개
	 *		가장 적은 빈도 값: 1 / 5 / 6 / 8 ... 1개
	 */
	int datas[3 * 3] = { 5, 3, 1, 4, 6, 4, 8, 4, 3 };

#if 1

#else
	std::map<int, int> map;

	int number = 0, count = 0;

	for (int idx = 0; idx < 9; idx++)
	{
		if (map.find(datas[idx]) == map.end()) // If not exists
		{
			map.insert({ datas[idx], 1 });
		}
		else // If exists
		{
			map.find(datas[idx])->second = map.find(datas[idx])->second + 1;
		}
	}

	for (auto it = map.begin(); it != map.end(); it++)
	{
		if (it->second >= count)
		{
			number = it->first;
			count = it->second;
		}
		if (it->second == 1)
		{
			std::cout << "가장 적은 빈도 값 : " << it->first << " ... " << it->second << "개" << std::endl;
		}
	}

	std::cout << "가장 많은 빈도 값 : " << number << " ... " << count << "개" << std::endl;
#endif

	return 1;
}
#endif