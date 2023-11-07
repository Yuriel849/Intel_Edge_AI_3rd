#pragma once
#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <iostream>
#include <mysql.h>

using namespace std;

class DataSource
{
public:
	void db_connect_test();
	string findImg(string uid);
	void getData(string uid, string& src, string& desc, string& entry_date);
	void setData(string uid, string src, string desc, string entry_date);
};

#endif