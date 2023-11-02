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
	~Gugudan();
	void SetParams();
	void Proc();
	void Display();
};

#endif