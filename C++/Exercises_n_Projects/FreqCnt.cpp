#include <iostream>
#include <map>

#if 0
int main()
{
	/* ���� ����/���� �󵵼��� ���� ����Ͻÿ�.
	 * ���� �亯
	 *		���� ���� �� ��: 4 ... 3��
	 *		���� ���� �� ��: 1 / 5 / 6 / 8 ... 1��
	 */
	const int length = 3 * 3;
	int datas[length] = { 5, 3, 1, 4, 6, 4, 8, 4, 3 };

#if 1
	// datas �迭 �� ���� value�� ���ÿ� index���̶�� �����غ���...
	// �� ������ histogram ���ϴ� ������
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
			std::cout << "���� ���� �� �� : " << i << " ... " << counts[i] << "��" << std::endl;
		}
	}
	for (size_t i = 0; i < length; i++)
	{
		if (_min_val == counts[i])
		{
			std::cout << "���� ���� �� �� : " << i << " ... " << counts[i] << "��" << std::endl;
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
			std::cout << "���� ���� �� �� : " << it->first << " ... " << it->second << "��" << std::endl;
		}
	}

	std::cout << "���� ���� �� �� : " << number << " ... " << count << "��" << std::endl;
#endif

	return 1;
}
#endif