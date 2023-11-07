#pragma once

#include <algorithm>    // std::sort

#include "ISP.h"

int main()
{
	// ����� ���� ��ǥ ��ȣ ���� ���Ͻÿ�. ���� �� �߰����� ���϶� (��ȣó���� �ſ� ȿ�����̸鼭�� �ſ� ������ �˰����̴�. ������ �ݺ� ���� �ð��� �����ɸ���.).
	int datas[] = { 6,4,2,5,9,8,4,5,2,1,5,3,6,5,2,1,1,4,5,2,23,3,6,6,1248,2,56,6,105,112 };
	int length = sizeof(datas) / sizeof(datas[0]); // 30
	sort(datas, datas + length);

	// vector ���
	std::vector<int> vDatas(datas, datas + length);
	std::sort(vDatas.begin(), vDatas.end());

	int major = datas[length / 2];
	int vMajor = vDatas[length / 2];

	cout << major << endl;
	cout << vMajor << endl;

	return 1;
}
