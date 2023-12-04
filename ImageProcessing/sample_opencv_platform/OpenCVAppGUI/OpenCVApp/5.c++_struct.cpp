//struct
//class
#include <iostream>
#include <vector>
#include <string>

//학생정보-성적
enum  {
	eEnglish,	//0
	eMath,		//eMath=5, 1->5
	eKorean,	//2->6
	eClassMax	//6->7
} ECLASS;
struct _stStudentInfo
{
	std::string name;
	//int eng, math, kor;
	int scores[eClassMax];
	//0 - english
	//1 - math
	//2 - Korean
	int sum, min, max;
	float avg;
};
//1?...50...하드코딩???
//scores[eEnglish] = 5;
//scores[eKorean] = 3;
//for (size_t score = 0; score < eClassMax; score++)


int sum(const int* const pData, size_t length)
{
	int sum = 0;
	for (size_t i = 0; i < length; i++) {
		sum += pData[i];
	}
	return sum;
}
float avg(const int* const pData, size_t length) {
	return sum(pData, length) / length;
}
int min(const int* const pData, size_t length){
	int min = pData[0];
	for (size_t i = 0; i < length; i++) {
		if (min > pData[i]) min = pData[i];
	}
	return min;
}
int max(const int* const pData, size_t length) {
	int max = pData[0];
	for (size_t i = 0; i < length; i++) {
		if (max < pData[i]) max = pData[i];
	}
	return max;
}
int main()
{
	/*
	if (0)
	{
		//namspace
		//{
		//}
		typedef unsigned char uchar;//사용자 타입 재지정
		typedef unsigned int uint;
		class MyClass
		{
		};
		//구조체, struct ......Class   ..... 
		//struct(public) == class(private,protected,public) ? ....1개의 차이점
		struct _stData
		{
			//서로 다른 종류의 데이터 항목을 결합하여
			//하나의 단위로 정의한 [데이터 타입]
			int score;
			double ratio;
			std::string name;
			int datas[100];
			int* pPreData = nullptr;
			int* pPostData = nullptr;
			std::vector<int> vLines;
			//함수
			void sum(int& a, int& b) { return a + b; }
			//클래스
			MyClass _myClass;
		};
		int a;
		_stData stData = { 10, 0.1, "hello", nullptr, nullptr };
		_stData* pstData = new _stData;// nullptr;
		//c
		//typedef struc[tagName]
		//{
		//	//데이타형
		//}[nickname];
		typedef struct _stDataC
		{
			int a;
			int b;
		}STDATAC;

		//useage
	}
	*/

	_stStudentInfo student;
	student.scores[eEnglish] = 90;
	student.scores[eMath] = 95;
	student.scores[eKorean] = 92;

	//1차
	//함수 ... sum, average, min, max
	//input scores[], length
	//return ... sum(int), average(float), min/max(int)

	//display
	//[이름]
	//english - ??, math - ??, korea - ??
	//sum - ??, average - ??, min - ??, max - ??

	//2차 - 자동으로 입력 및 성적 정보 출력
	//사용자로부터 입력을 받습니다.
	//struct에 string name을 입력 받아요.
	//각 eng, math, kor 점수를 입력 받아요
	//위 display로 출력을 합니다.
	//Q입력을 받으면 더 이상 입력을 하지 않습니다.
	std::vector<_stStudentInfo> vStudent;
	while (true)
	{
		std::cin >> student.name;
		if (student.name == "Q")break;
		std::cin >> student.scores[eEnglish];
		std::cin >> student.scores[eMath];
		std::cin >> student.scores[eKorean];

		
		vStudent.push_back(student);
	}


	for (size_t i =	0; i < vStudent.size(); i++)
	{
		_stStudentInfo* pStudent = &vStudent[i];

		std::cout << sum(pStudent->scores, eClassMax);
		std::cout << avg(pStudent->scores, eClassMax);
		std::cout << min(pStudent->scores, eClassMax);
		std::cout << max(pStudent->scores, eClassMax);

	}


	/*
	if (false)
	{
		//현재 코딩 스타일
		1. C / C++ 코드 이종코드
			int arr[], int* p = nullptr, const int* const p
			코드테스트...UnitTest...Aging(invalid range...out of range...die)
			2. 함수 / 변수
			변수명...name...의미없음...a->abc i / j / k / n / m / l ->
			a, b, c, d......a ? ...
			상수 1, 10, 3, ....... ? ... enum, TRUE(1), true
			if (1...true... > )//true or false
				3. 일반화 못함
				3가지 문제가 있습니다...3가지를 해결
				sum...(a + b + c)
				avg...(a + b + c) / 3...sum / 3...sum / length
				for 손가락이 마르고 닿도록..코딩을 열심 밤낮수정
					코드테스트...UnitTest...Aging(invalid range...out of range...die)
					for...N개...array[N]
					{ for != a + b + c }  .... for == N
						4. 변수 / 함수...이름의 중복성
					{
					int a = 1;
												{//생성
													int a = 0;
												}//소멸
									{//생성
										int a = 2;
									}//소멸
					cout << a; ? ? ...0..2..1(정답입니다~)
					}
		int sum;
		void sum();
		std::cout << sum
			5. pointer...array[N]
			index....value
			[0][1][2][3][4][][][][][][][][][][][][][][N - 1]
			index...access..
			value...array[index]
			for 0...N - 1
				array[index]
				pointer....start point
				[0][1][2][3][4][][][][][][][][][][][][][][N - 1]
				|| st || st + 10
				pointer 4, N = 10 ...partial
				6. 함수 매개변수 ...외부 입력
				단순 기능만 해...명령..sum / avg / min / max
				최소한의 정보 or 전체를 가르키게 해줌
				const int* const pDatas....length = > sum
				int a, b, c
				sum(int* a, int b[], int c)...N ?
			{ a, b, c
			}
		7. sum(struct * pSt)
	}
	*/
}







