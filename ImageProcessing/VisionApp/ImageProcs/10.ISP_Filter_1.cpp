#pragma once

#include <algorithm>    // std::sort

#include "ISP.h"

int main()
{
	// 노이즈가 없는 대표 신호 값을 정하시오. 정렬 후 중간값을 구하라 (신호처리에 매우 효과적이면서도 매우 간단한 알고리즘이다. 단점은 반복 사용시 시간이 오래걸린다.).
	int datas[] = { 6,4,2,5,9,8,4,5,2,1,5,3,6,5,2,1,1,4,5,2,23,3,6,6,1248,2,56,6,105,112 };
	int length = sizeof(datas) / sizeof(datas[0]); // 30
	sort(datas, datas + length);

	// vector 사용
	std::vector<int> vDatas(datas, datas + length);
	std::sort(vDatas.begin(), vDatas.end());

	int major = datas[length / 2];
	int vMajor = vDatas[length / 2];

	cout << major << endl;
	cout << vMajor << endl;

	return 1;
}
