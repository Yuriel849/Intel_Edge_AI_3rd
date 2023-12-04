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
		string name; 
		//int eng, kor, math;
		int sum, min, max;
		float avg;
		//"subjectName", score//
		//string ... new []...N ... [i:subject]
		//int    ... new []...N         [i+1:score]
		//"pair"
		std::map<string, int> mTable;
	};

	StudentInfo stStudentInfo;
	//std::map<string, StudentInfo> mTable;
};
//std::map<string, StudentScore> mTable;

//std::map<string, void*> mTable;
//int*  void*  ... (int*)(void*)
//[](uchar 0)



