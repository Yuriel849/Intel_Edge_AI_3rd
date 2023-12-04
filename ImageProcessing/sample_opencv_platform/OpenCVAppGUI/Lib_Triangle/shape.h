#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class Shape
{
public:
	Shape();//ctor
	virtual ~Shape();//dtor

	//action function
	void SetVertexCnt(int points);
	int GetVertexCnt();
	//순수 가상함수
	//virtual void ShowShapeInfo() = 0;
	//가상 함수
	virtual void ShowShapeInfo();

private:
	//variables
	int _points = 0;
};

