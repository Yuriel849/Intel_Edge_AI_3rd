#pragma once
#ifndef GUGUDAN_H
#define GUGUDAN_H

class Gugudan
{
private:
	int DanS, DanE, StepS, StepE;
	std::string msg = "";
public:
	Gugudan();
	void setParams();
	void proc();
	void display();
};

#endif