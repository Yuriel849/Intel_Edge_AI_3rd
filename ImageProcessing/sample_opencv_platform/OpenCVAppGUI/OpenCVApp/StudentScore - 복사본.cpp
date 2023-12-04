#include "StudentScore.h"

StudentScore::StudentScore()
{

}

StudentScore::~StudentScore()
{
}

void StudentScore::SetStudentName(string Name)
{
	stStudentInfo.name = Name;
}

void StudentScore::SetSubjectScore(string subject, int score)
{
	string str = subject;
	//c-style
	for (size_t i = 0; i < str.size(); i++)
	{
		str[i] = std::toupper(str[i]);
	}
	//c++ lambda style
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c) { return toupper(c); });
	if (str == "KOR") stStudentInfo.kor = score;
	else if (str == "ENG") stStudentInfo.eng = score;
	else if (str == "MATH") stStudentInfo.math = score;
	else
		cout << "Subject {Kor, Eng, Math} Only" << endl;
}

void StudentScore::DoCalc()
{
	//홍길동 = 국어:90, 영어 : 90, 수학 : 98, 미술 : 88, 음악 : 94, 역사 : 99총합 = ? ? , 평균 = ? ? , 최소 = ? ? , 최대 = ? ?
	cout << stStudentInfo.name << " => "
		<< "국어 : " << stStudentInfo.kor << "\t"
		<< "영어 : " << stStudentInfo.eng << "\t"
		<< "수학 : " << stStudentInfo.math << "\t"
		<< "총합 : " << GetSum() << "\t"
		<< "평균 : " << GetAvg() << "\t"
		<< "최소 : " << GetMin() << "\t"
		<< "최대 : " << GetMax()
		<< endl;
		

}

int StudentScore::GetSum()
{
	return (stStudentInfo.kor+stStudentInfo.eng+stStudentInfo.math);
}

float StudentScore::GetAvg()
{
	return GetSum()/3.0;
}

int StudentScore::GetMin()
{
	int score[3] = { stStudentInfo.kor,
	stStudentInfo.eng,stStudentInfo.math };
	std::sort(score, score + 3);
	return score[0];
}

int StudentScore::GetMax()
{
	int score[3] = { stStudentInfo.kor,
	stStudentInfo.eng,stStudentInfo.math };
	std::sort(score, score + 3);
	return score[3-1];
}
