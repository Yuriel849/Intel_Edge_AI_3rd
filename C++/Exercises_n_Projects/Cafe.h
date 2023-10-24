#pragma once
#ifndef CAFE_H
#define CAFE_H

#include <string>
using namespace std;

#include "cafemenu.h"

// Cafe Class는 CafeMenu Class를 이용해서 제품 데이터를 읽어들이고 출력한 후 주문을 받아 주문 내역을 출력하고,
//		주문이 끝나면 그날의 매출통계를 출력한다.
class Cafe
{
private:
	CafeMenu menu[12];
	int sales_total[12] = {}; // 모든 원소를 0으로 초기화
	int total_sales = 0;
	int total = 0;
	int selection[100] = {};
	int input = 0;
	int cnt = 0;
	int selectFlag = 0;
public:
	Cafe();
	void run();
	void printList();
	void printSummary();
};
#endif