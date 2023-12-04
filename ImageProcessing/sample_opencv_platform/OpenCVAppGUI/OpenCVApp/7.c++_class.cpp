#include "Calc.h"

//내장데이타타입
//int
//array[]
//struct
Calc calc_global;//전역,global//프로그램 시작/종료 시 Calc 생성/소멸

int main()
{
	{
		Calc calc_local;//지역, local
		//함수/Logic 블럭단위{} 시작/종료 시 Calc 생성/소멸
		//내장데이타타입
		//int
		//array[]
		//struct
	}

	{
		
		Calc* pCalc = new Calc();//동적, dynamic memory allocation
		//int* pData = new int[100];
		//new 생성

		try
		{
			//logic
			//exception
			//return;
		}
		catch (const std::exception&)
		{
			if (pCalc != nullptr)
			{
				delete pCalc; //delete 소멸
				pCalc = nullptr;
			}
			//if(pData!=nullptr)
			//{delete [] pData; pData = nullptr;}
			return -1;
		}
		if (pCalc != nullptr)
		{
			delete pCalc; //delete 소멸
			pCalc = nullptr;
		}
		//if(pData!=nullptr)
		//{delete [] pData; pData = nullptr;}

		

	}




	if(true)
	{
		Calc calc;

		
		calc.Clear();
		//calc.SetValue(1, 2, '+');
		int data[3] = { 1,2,3 };

		calc.sum(data, 3);
		cout << "합은 " << calc.GetResult() << endl;
		calc.Clear();
		calc.SetValue(1, 2, '+');
		calc.DoSum();
		cout << "합은 " << calc.GetResult() << endl;
	}
	
	if(false)
	{
		Calc* pCalc = new Calc();

		int data[3] = { 1,2,3 };
		pCalc->sum(data, 3);
		cout << "합은 " << pCalc->GetResult() << endl;
		pCalc->Clear();
		pCalc->SetValue(1, 2, '+');
		pCalc->DoSum();
		cout << "합은 " << pCalc->GetResult() << endl;

		//return 1;

		if (pCalc != nullptr)
		{
			delete pCalc;
			pCalc = nullptr;
		}
	}
	


	{
		//smart pointer
		//Calc* pCalc = new Calc();
		std::shared_ptr<Calc> pCalc = std::make_shared<Calc>(1, 1, '+');

		int data[3] = { 1,2,3 };
		pCalc->sum(data, 3);
		cout << "합은 " << pCalc->GetResult() << endl;
		pCalc->Clear();
		pCalc->SetValue(1, 2, '+');
		pCalc->DoSum();
		cout << "합은 " << pCalc->GetResult() << endl;

	}

	return 1;
}