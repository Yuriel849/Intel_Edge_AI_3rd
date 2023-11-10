#include <iostream>
#include <map>

#if 0
int main()
{
	/* 가장 많은/적은 빈도수의 값을 출력하시오.
	 * 예상 답변
	 *		가장 많은 빈도 값: 4 ... 3개
	 *		가장 적은 빈도 값: 1 / 5 / 6 / 8 ... 1개
	 */
	const int length = 3 * 3;
	int datas[length] = { 5, 3, 1, 4, 6, 4, 8, 4, 3 };

#if 1
	// datas 배열 속 값은 value인 동시에 index값이라고 생각해보면...
	// 이 문제는 histogram 구하는 문제다
	int counts[length] = { 0, };
	// value... -> ...index
	int _max_val = -1;
	int _min_val = 1000;

	for (size_t i = 0; i < length; i++)
	{
		counts[datas[i]]++;
		if (_max_val < counts[datas[i]]) { _max_val = counts[datas[i]]; }
		if (_min_val > counts[datas[i]]) { _min_val = counts[datas[i]]; }
	}

	// display
	for (size_t i = 0; i < length; i++)
	{
		if (_max_val == counts[i])
		{
			std::cout << "가장 많은 빈도 값 : " << i << " ... " << counts[i] << "개" << std::endl;
		}
	}
	for (size_t i = 0; i < length; i++)
	{
		if (_min_val == counts[i])
		{
			std::cout << "가장 적은 빈도 값 : " << i << " ... " << counts[i] << "개" << std::endl;
		}
	}
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