#include <iostream>
#include <map>

#if 1
int main()
{
	/* ���� ����/���� �󵵼��� ���� ����Ͻÿ�.
	 * ���� �亯
	 *		���� ���� �� ��: 4 ... 3��
	 *		���� ���� �� ��: 1 / 5 / 6 / 8 ... 1��
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
			std::cout << "���� ���� �� �� : " << it->first << " ... " << it->second << "��" << std::endl;
		}
	}

	std::cout << "���� ���� �� �� : " << number << " ... " << count << "��" << std::endl;
#endif

	return 1;
}
#endif