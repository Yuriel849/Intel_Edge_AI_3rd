#include "StudentScore.h"

int main()
{
	if (false)
	{
		string strName; int ScoreKor, ScoreEng, ScoreMath;
		cout << "INPUT Student Name : ";
		cin >> strName;
		cout << "INPUT Student Subject {Kor, Eng, Math} Score : ";
		cin >> ScoreKor >> ScoreEng >> ScoreMath;

		StudentScore ss;
		ss.SetStudentName(strName);
		ss.SetSubjectScore("kor", ScoreKor);
		ss.SetSubjectScore("ENG", ScoreEng);
		ss.SetSubjectScore("Math", ScoreMath);
		ss.DoCalc();

	}


	
	
	vector<StudentScore> vStudent;
	StudentScore ss;
	string strName, strSubject; int Score;

	while (true)
	{
		cout << "INPUT Student Name ( Quit : Q, q ) : ";
		cin >> strName;

		if (strName == "Q" || strName == "q") {
			break;
		}
		ss.SetStudentName(strName);

		while (true)
		{
			cout << "INPUT Student Subject {Kor, Eng, Math}" << endl;
			cout << "Subject Name  : "; cin >> strSubject;

			if (strSubject == "Q" || strSubject == "q") {
				ss.DoCalc(); 
				break;
			}

			cout << "Subject Score : "; cin >> Score;


			
			ss.SetSubjectScore(strSubject, Score);

		}

		vStudent.push_back(ss);
	}
	
	cout << "[ Score Table ]" << endl; for (int i= 0; i < 50; i++) cout << "--" ;
	cout << endl;
	for (auto iter = vStudent.begin(); iter != vStudent.end(); iter++)
	{
		iter->DoCalc();
	}
	





	return 1;
}