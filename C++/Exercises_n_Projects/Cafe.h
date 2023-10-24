#pragma once
#ifndef CAFE_H
#define CAFE_H

#include <string>
using namespace std;

#include "cafemenu.h"

// Cafe Class�� CafeMenu Class�� �̿��ؼ� ��ǰ �����͸� �о���̰� ����� �� �ֹ��� �޾� �ֹ� ������ ����ϰ�,
//		�ֹ��� ������ �׳��� ������踦 ����Ѵ�.
class Cafe
{
private:
	CafeMenu menu[12];
	int sales_total[12] = {}; // ��� ���Ҹ� 0���� �ʱ�ȭ
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