#pragma once
#ifndef GUGUDAN_H
#define GUGUDAN_H

#include <iostream>
#include <string>
#include <vector>

class Gugudan
{
private:
	int DanS, DanE, StepS, StepE;
	std::string msg = "";
	std::vector<std::string> vMsg;
public:
	Gugudan();
	~Gugudan();
	void SetParams(); // Input
	void Proc();	  // Function
	void Display();	  // Output
};

#endif