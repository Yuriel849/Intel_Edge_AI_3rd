#include "KPhone.h"

KPhone::KPhone()
	:strNumber("000-0000-0000")
	, isConnected(false)
{
	cout << "KPhone::Ctor" << endl;
}

KPhone::~KPhone()
{
	cout << "KPhone:Dtor" << endl;
}

int KPhone::Send()
{
	//check number
	if (strNumber == "000-0000-0000")
	{
		cout << "wrong number" << endl;
		return -1;
	}

	//check on the phone
	if (isConnected == true)
	{
		cout << "on the phone" << endl;
		return -1;
	}

	cout << "calling" << endl;

	cout << "linked" << endl;

	isConnected = true;

	cout << "communication start" << endl;
	//wait(5000);
	////Cancel
	//cout << "communication finish" << endl;
	//isConnected = false;

	return 0;
}

int KPhone::Cancel()
{
	cout << "cancel button activated" << endl;

	//Cancel
	cout << "communication finish" << endl;
	isConnected = false;
	return 0;
}

int KPhone::Receive()
{
	if (isConnected == true)
	{
		cout << "on the phone" << endl;
		return -1;
	}

	cout << "linked" << endl;

	isConnected = true;

	cout << "communication start" << endl;

	////Cancel
	//cout << "communication finish" << endl;
	//isConnected = false;
	return 0;
}

int KPhone::Numbers(string _strNumber)
{
	strNumber = _strNumber;
	return 0;
}

int KPhone::Numbers(int* pAudioData, int length)
{
	//pAudioData 분석
	//음석인식 알고리즘 넣어줘
	string number = "010-1234-5678";// DoAnalysisAudioData(pAudioData, length);
	strNumber = number;
	//결과로 문자를 반환
	return 0;
}
