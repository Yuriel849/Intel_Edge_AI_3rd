#pragma once
#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

class DataSource
{
private:
	unsigned int timeout_sec = 1;
public:
	string findImg(string uid, string& time);
	void addUser(string uid, string src);
	void setEntry(string uid);
	bool exists(string uid);
	bool isActive(string uid);
	void deactivate(string uid);
};

#endif