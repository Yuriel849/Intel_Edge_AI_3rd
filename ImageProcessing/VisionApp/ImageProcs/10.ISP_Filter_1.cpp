#pragma once

#include <algorithm>    // std::sort

#include "ISP.h"

int main()
{
	int datas[] = { 6,4,2,5,9,8,4,5,2,1,5,3,6,5,2,1,1,4,5,2,23,3,6,6,1248,2,56,6,105,112 };
	int length = sizeof(datas) / sizeof(datas[0]); // 30

	// ����� ���� ��ǥ ��ȣ ���� ���Ͻÿ�. ���� �� �߰����� ���϶� (��ȣó���� �ſ� ȿ�����̸鼭�� �ſ� ������ �˰����̴�. ������ �ݺ� ���� �ð��� �����ɸ���.).
	sort(datas, datas + length);
	cout << datas[length / 2] << endl;



	return 0;
}
