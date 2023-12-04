#pragma once
#include "common.h"

class KPhone
{
	string strAA[3] = { "a" ,"a" ,"a" };
public:
	KPhone();
	~KPhone();
	int Send();			// : 전화를 걸다
	int Cancel();		//전화 끊기

	int Receive();		// : 전화를 받다
	int Numbers(string _strNumber);// : 전화번호를 입력한다.
	int Numbers(int* pAudioData, int length);

private:
	string strNumber;	// : 전화번호
	bool isConnected;	// : 전화중인가 ?
};

