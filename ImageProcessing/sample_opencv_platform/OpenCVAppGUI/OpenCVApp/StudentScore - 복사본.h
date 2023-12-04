#pragma once
#include "common.h"

class StudentScore
{
public:
	StudentScore();
	~StudentScore();

	void SetStudentName(string Name);
	void SetSubjectScore(string subject, int score);
	void DoCalc();
	

private:
	int GetSum();
	float GetAvg();
	int GetMin();
	int GetMax();

	struct StudentInfo
	{
		string name; int eng, kor, math;
		int sum, min, max;
		float avg;

	};

	StudentInfo stStudentInfo;
};

