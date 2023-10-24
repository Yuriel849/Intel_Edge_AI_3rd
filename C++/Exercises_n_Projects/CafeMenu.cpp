#pragma once

#include <iostream>
using namespace std;

#include "cafemenu.h"

// constructor
CafeMenu::CafeMenu()
{
	this->name = "Ä¿ÇÇ";
	this->size = "Standard";
	this->price = 1000;
}

CafeMenu::CafeMenu(string name, string size, int price)
{
	this->name = name;
	this->size = size;
	this->price = price;
}

// getters
string CafeMenu::getName()
{
	return this->name;
}

string CafeMenu::getSize()
{
	return this->size;
}

int CafeMenu::getPrice()
{
	return this->price;
}

// setters
void CafeMenu::setName(string new_name)
{
	this->name = new_name;
}

void CafeMenu::setSize(string new_size)
{
	this->size = new_size;
}

void CafeMenu::setPrice(int new_price)
{
	this->price = new_price;
}
