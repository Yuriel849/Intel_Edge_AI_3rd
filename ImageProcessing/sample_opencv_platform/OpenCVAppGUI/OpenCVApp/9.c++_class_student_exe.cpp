#include "StudentScore_rev1.0.h"

int main()
{
	if (false)
	{
		//name, scorekor, eng, math
		string strName;
		int scoreKor, scoreEng, scoreMath;
		cout << "Input Student Name :";
		cin >> strName;
		cout << "Input Student Subject {Kor, Eng, Math} Score : ";
		cin >> scoreKor >> scoreEng >> scoreMath;
		StudentScore ss;
		ss.SetStudentName(strName);
		ss.SetSubjectScore("kor", scoreKor);
		ss.SetSubjectScore("ENG", scoreEng);
		ss.SetSubjectScore("Math", scoreMath);
		ss.DoCalc();
	}
	//해보기
	//SetSubjectScore에 사용자가 입력한 subject와 score를 
	//Q,q로 종료될기까지 입력 받아 그 결과를 출력하세요
	// 결과 아래>>
	// 홍길동 = 국어:90, 영어 : 90, 수학 : 98, 미술 : 88, 
	// 음악 : 94, 역사 : 99 |총합 = ?? , 평균 = ?? , 최소 = ?? , 최대 = ??
	//
	vector< StudentScore> vStudent;

	//int a = 1; 2, 3, 4 ....0;
	//int* pA = new int[1];



	StudentScore ss;

	string strName, strSubjectName;
	while (true)
	{
		int score;
		cout << "Input Student Name :";
		cin >> strName;
		if (strName == "Q" || strName == "q")
			break;
		ss.SetStudentName(strName);

		while (true)
		{
			cout << "Input Subject Name : ";
			cin >> strSubjectName;

			if (strSubjectName == "Q" || strSubjectName == "q")
			{
				ss.DoCalc();
				break;
			}
			cout << "Input Subject Score : ";
			cin >> score;

			ss.SetSubjectScore(strSubjectName, score);
		}

		vStudent.push_back(ss);
	}

	//for (size_t i = 0; i < vStudent.size(); i++)
	//{
	//	vStudent[i].DoCalc();
	//}

	cout << "[ Score Table ]" << endl; for (int i = 0; i < 50; i++) cout << "--";
	cout << endl;
	for (auto iter = vStudent.begin(); iter != vStudent.end(); iter++)
	{
		iter->DoCalc();
	}


	return 1;
}