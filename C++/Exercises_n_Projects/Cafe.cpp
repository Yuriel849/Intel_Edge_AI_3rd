#pragma once

#include <iostream>
using namespace std;

#include "cafe.h"

Cafe::Cafe() // Set up menu items
{
	menu[0].setName("카페_아메리카노");
	menu[0].setSize("Short");
	menu[0].setPrice(3600);

	menu[1].setName("카페_아메리카노");
	menu[1].setSize("Tall");
	menu[1].setPrice(4100);

	menu[2].setName("카페_라떼");
	menu[2].setSize("Short");
	menu[2].setPrice(4100);

	menu[3].setName("카페_라떼");
	menu[3].setSize("Tall");
	menu[3].setPrice(4600);

	menu[4].setName("카푸치노");
	menu[4].setSize("Short");
	menu[4].setPrice(4100);

	menu[5].setName("카푸치노");
	menu[5].setSize("Tall");
	menu[5].setPrice(4600);

	menu[6].setName("카페모카");
	menu[6].setSize("Short");
	menu[6].setPrice(4100);

	menu[7].setName("카페모카");
	menu[7].setSize("Tall");
	menu[7].setPrice(4600);

	menu[8].setName("카라멜_마키아또");
	menu[8].setSize("Short");
	menu[8].setPrice(5100);

	menu[9].setName("카라멜_마키아또");
	menu[9].setSize("Tall");
	menu[9].setPrice(5600);

	menu[10].setName("스타벅스_돌체_라떼");
	menu[10].setSize("Short");
	menu[10].setPrice(5100);

	menu[11].setName("스타벅스_돌체_라떼");
	menu[11].setSize("Tall");
	menu[11].setPrice(5600);
}

void Cafe::run()
{
	while (1) // Infinite loop until broken by user input of '0'
	{
		// Reset variables
		total = 0;
		input = 0;
		cnt = 0;

		printList(); // Print menu for user to choose from
		cout << endl;

		do
		{
			cin >> input;
			selection[cnt++] = input - 1;
		} while (input != 0); // Accept user input of numbers until '0' is entered

		if (selection[0] == -1) // If user enters '0', break infinite loop; user entry of '0' is saved as '-1'
		{
			printSummary();
			break;
		}

		for (int i = 0; i < cnt; i++)
		{
			if (selection[i] < -1 || 11 < selection[i]) // If user enters number less than 1 or greater than 12
			{
				cout << selection[i]+1 << "는/은 없는 메뉴입니다..." << endl;
				selectFlag = 1;
				break;
			}
		}

		if (selectFlag == 1) // If user entered unavailable menu item, continue
		{
			selectFlag = 0;
			continue;
		}
		
		cout << "주문한 상품 : " << endl;
		for (int i = 0; i < cnt-1; i++)
		{

			cout << menu[selection[i]].getName() + " " << menu[selection[i]].getSize() + " " << menu[selection[i]].getPrice() << endl;
			sales_total[selection[i]] += 1;
			total += menu[selection[i]].getPrice();
		}
		cout << "합계 : " << total << "원" << endl;
		total_sales += total;
	}
}

void Cafe::printList()
{
	cout << "============ CAFE MENU 리스트 ============" << endl;
	cout << "[ 1] 카페_아메리카노 Short 3.6" << endl;
	cout << "[ 2] 카페_아메리카노 Tall 4.1" << endl;
	cout << "[ 3] 카페_라떼 Short 4.1" << endl;
	cout << "[ 4] 카페_라떼 Tall 4.6" << endl;
	cout << "[ 5] 카푸치노 Short 4.1" << endl;
	cout << "[ 6] 카푸치노 Tall 4.6" << endl;
	cout << "[ 7] 카페모카 Short 4.1" << endl;
	cout << "[ 8] 카페모카 Tall 4.6" << endl;
	cout << "[ 9] 카라멜_마키아또 Short 5.1" << endl;
	cout << "[10] 카라멜_마키아또 Tall 5.6" << endl;
	cout << "[11] 스타벅스_돌체_라떼 Short 5.1" << endl;
	cout << "[12] 스타벅스_돌체_라떼 Tall 5.6" << endl;
}

void Cafe::printSummary()
{
	cout << "================ 매출 통계 ===============" << endl;
	for (int i = 0; i < 12; i++)
	{
		if (sales_total[i] > 0)
		{
			cout << menu[i].getName() + " " << menu[i].getSize() + " " << sales_total[i] << "개" << endl;
		}
	}
	cout << "매출액 총계 : " << total_sales << "원" << endl;

}