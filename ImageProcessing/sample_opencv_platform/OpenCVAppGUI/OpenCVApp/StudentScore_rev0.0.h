#pragma once
#include "common.h"

class StudentScore
{
public:
	StudentScore();
	~StudentScore();
private:
	int GetSum();
	float GetAvg();
	int GetMin();
	int GetMax();
	struct StudentInfo
	{
		string name;
		int eng, kor, math;//각과목 성적
		int sum, min, max;
		float avg;
	};
	StudentInfo studentinfo;

public:
//기능
//입력 학생 이름
	int SetStudentName(string name);
//과목,성적입력
	int SetSubjectScore(string subject, int score);
//결과 산출, sum, avg, min, max
	int DoCalc();

};

