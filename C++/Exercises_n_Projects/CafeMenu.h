#pragma once
#ifndef CAFE_MENU_H
#define CAFE_MENU_H

#include <string>
using namespace std;

// CafeMenu Class를 이용하여 제품을 나타낸다.
class CafeMenu
{
private:
	string name;
	string size;
	int price;
public:
	// constructor
	CafeMenu();
	CafeMenu(string name, string size, int price);
	// getters
	string getName();
	string getSize();
	int getPrice();
	// setters
	void setName(string new_name);
	void setSize(string new_size);
	void setPrice(int new_price);
};
#endif