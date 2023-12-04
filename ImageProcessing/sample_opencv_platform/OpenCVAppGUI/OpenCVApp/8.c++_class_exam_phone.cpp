#include "KPhone.h"

int main()
{
	//전화 걸기
	{
		//전화기를 든다
		KPhone* pKphone = new KPhone();

		//전화 번호 입력
		//pKphone->Numbers("010-1234-5678");
		int* pAudio = new int[11] {
			0,1,0,1,2,3,4,5,6,7,8
		};
		int length = 11;
		pKphone->Numbers(pAudio, length);//revision 2.0
		//전화 걸기
		pKphone->Send();
		pKphone->Cancel();//revision 3.0

		//전화기를 내린다
		if (pKphone != nullptr)
		{
			delete pKphone;
			pKphone = nullptr;
		}
	}
	

	//전화 받기
	{
		//전화기를 듣다
		KPhone* pKphone = new KPhone();

		//전화 걸기
		pKphone->Receive();

		pKphone->Cancel();//revision 2.0

		//전화기를 내린다
		if (pKphone != nullptr)
		{
			delete pKphone;
			pKphone = nullptr;
		}
	}




	return 1;
}