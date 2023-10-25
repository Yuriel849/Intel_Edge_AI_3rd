#pragma once

#include <iostream>
using namespace std;

#include "cafe.h"

Cafe::Cafe() // Set up menu items
{
	menu[0].setName("ī��_�Ƹ޸�ī��");
	menu[0].setSize("Short");
	menu[0].setPrice(3600);

	menu[1].setName("ī��_�Ƹ޸�ī��");
	menu[1].setSize("Tall");
	menu[1].setPrice(4100);

	menu[2].setName("ī��_��");
	menu[2].setSize("Short");
	menu[2].setPrice(4100);

	menu[3].setName("ī��_��");
	menu[3].setSize("Tall");
	menu[3].setPrice(4600);

	menu[4].setName("īǪġ��");
	menu[4].setSize("Short");
	menu[4].setPrice(4100);

	menu[5].setName("īǪġ��");
	menu[5].setSize("Tall");
	menu[5].setPrice(4600);

	menu[6].setName("ī���ī");
	menu[6].setSize("Short");
	menu[6].setPrice(4100);

	menu[7].setName("ī���ī");
	menu[7].setSize("Tall");
	menu[7].setPrice(4600);

	menu[8].setName("ī���_��Ű�ƶ�");
	menu[8].setSize("Short");
	menu[8].setPrice(5100);

	menu[9].setName("ī���_��Ű�ƶ�");
	menu[9].setSize("Tall");
	menu[9].setPrice(5600);

	menu[10].setName("��Ÿ����_��ü_��");
	menu[10].setSize("Short");
	menu[10].setPrice(5100);

	menu[11].setName("��Ÿ����_��ü_��");
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
				cout << selection[i]+1 << "��/�� ���� �޴��Դϴ�..." << endl;
				selectFlag = 1;
				break;
			}
		}

		if (selectFlag == 1) // If user entered unavailable menu item, continue
		{
			selectFlag = 0;
			continue;
		}
		
		cout << "�ֹ��� ��ǰ : " << endl;
		for (int i = 0; i < cnt-1; i++)
		{

			cout << menu[selection[i]].getName() + " " << menu[selection[i]].getSize() + " " << menu[selection[i]].getPrice() << endl;
			sales_total[selection[i]] += 1;
			total += menu[selection[i]].getPrice();
		}
		cout << "�հ� : " << total << "��" << endl;
		total_sales += total;
	}
}

void Cafe::printList()
{
	cout << "============ CAFE MENU ����Ʈ ============" << endl;
	cout << "[ 1] ī��_�Ƹ޸�ī�� Short 3.6" << endl;
	cout << "[ 2] ī��_�Ƹ޸�ī�� Tall 4.1" << endl;
	cout << "[ 3] ī��_�� Short 4.1" << endl;
	cout << "[ 4] ī��_�� Tall 4.6" << endl;
	cout << "[ 5] īǪġ�� Short 4.1" << endl;
	cout << "[ 6] īǪġ�� Tall 4.6" << endl;
	cout << "[ 7] ī���ī Short 4.1" << endl;
	cout << "[ 8] ī���ī Tall 4.6" << endl;
	cout << "[ 9] ī���_��Ű�ƶ� Short 5.1" << endl;
	cout << "[10] ī���_��Ű�ƶ� Tall 5.6" << endl;
	cout << "[11] ��Ÿ����_��ü_�� Short 5.1" << endl;
	cout << "[12] ��Ÿ����_��ü_�� Tall 5.6" << endl;
}

void Cafe::printSummary()
{
	cout << "================ ���� ��� ===============" << endl;
	for (int i = 0; i < 12; i++)
	{
		if (sales_total[i] > 0)
		{
			cout << menu[i].getName() + " " << menu[i].getSize() + " " << sales_total[i] << "��" << endl;
		}
	}
	cout << "����� �Ѱ� : " << total_sales << "��" << endl;

}