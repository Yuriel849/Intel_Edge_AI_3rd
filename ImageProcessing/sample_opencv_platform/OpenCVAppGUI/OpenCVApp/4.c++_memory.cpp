//memory
//alloc, release
//pointer vs reference
//1D array and index
//
#include <iostream>
#include <memory>
using namespace std;
//1) int sum(int* const pData, int size) {
//2) int sum(const int* pData, int size) {
//3) int sum(const int* const pData, int size) {
//int sum(int* pData, int size) {
int sum(const unsigned int* const pData, int length) {
	int sum = 0;
	for (size_t i = 0; i < length; i++) { sum += pData[i]; }
	return sum;
}
//partial_sum 함수 start_index = 5, finish_index = 23
int sum(const unsigned int* const pData, int length,
	int start_index/*=0*/, 
	int finish_index/*=length*/){
	if (finish_index >= length) return -1;
	int sum = 0;
	for (size_t i = start_index; i <= finish_index; i++) { sum += pData[i]; }
	return sum;
}
//partial_sum 함수 start_row,start_col (1,1), finish_row, finish_col (3,3)
int sum(const unsigned int* const pData, int width, int height,
	int start_row, int start_col, int finish_row, int finish_col) {
	int sum = 0;
	//코드 작성
	for (size_t row = start_row; row <= finish_row; row++)
	{
		for (size_t col = start_col; col <= finish_col; col++)
		{
			size_t index = (row) * width + (col);
			sum+=pData[index];
		}
	}
	return sum;
}
int main()
{
	{
		//memory
		int a; double b; char c;
		int* pA; double* pB; char* pC;
		//array
		int arr[100] = { 0, };//100정해졌을때,

		//dynamic memory alloc
		int sz = 100000;//메모리 크기 정해짐
		//memory create
		int* pData = new int[sz] {0, };
		//CShape* pShape = new CCircle();//CCircle from CShape
		//memory delete
		if (pData != nullptr) {
			delete[] pData; pData = nullptr;
		}
		//RAII (Resource Acquisition Is Initialization)
		//C++11 표준... smart pointer 도입
		//unique_ptr:하나의 스마트 포인터만 특정 객체를 소유
		//        design pattern : singletone
		// 
		//shared_ptr:참조 횟수가 계산(Reference Count)
		/*
		class int
		{
			unsigned int reference_count=0
			int();//create
			~int()//destroy
			{
				for (size_t rc = 0; rc < reference_count; rc++)
				{
					if (this_mem != nullptr) {
						delete[] this_mem; this_mem = nullptr;
					}
				}
			}

			//int* pData1 = new int[sz] {0, };->reference_count:1
			//int* pData2 = new int[sz] {0, };->reference_count:2
			//int* pData3 = new int[sz] {0, };->reference_count:3
			int* new operator
			{
				reference_count++;
			}
		}
		*/
		//weak_ptr:하나 이상의 shared_ptr 참조가 있는 
		//		객체에 대한 접근을 제공, 소유자의 수에는 포함되지 않음
		std::unique_ptr<int> pDatas = std::make_unique<int>(sz);
		std::shared_ptr<int> pTypes = std::make_shared<int>(sz);

		//int* pData = nullptr;//메모리를 사용할꺼야
		pData = new int[sz] {0, };//동적 메모리 생성
		//memory leak...메모리 누수
		/*if (pData != nullptr) {
			delete[] pData; pData = nullptr;
		}*/


		//pointer and reference
		int dA = 10;
		int* pdA = &dA;
		/*
		int function_name(int a)//int a = int obj :: copy
		{
		내부데이타 != 외부데이타, 단절
		}
		int function_name(int* pA)//int* pA = int* obj : pointer
		{
		내부데이타(pA 주소,pointer) == 외부데이타 변경
		}
		int function_name(int* pA)//int* pA = &int obj : pointer
		int function_name(int& A)//int& A = int obj nickname

		void swap_A(int lhs, int rhs) //swap_A(a(10), b(20)) -> a:10, b:20
		{
			int tmp;
			tmp = lhs;//tmp = 10
			lhs = rhs;//10->20 , 내부데이타 변경
			rhs = tmp;//20->10 , 내부데이타 변경
		}
		void swap_B(int* lhs, int* rhs)//swap_B(&a(10), &b(20)) -> a:20, b:10
		{
			int tmp;
			tmp = *lhs;//tmp = 10
			*lhs = *rhs;//10->20 ,외부데이타 변경
			*rhs = tmp;//20->10 ,외부데이타 변경
		}
		*/
		//3가지 상수 포인터
		int num = 10; int* pnum = &num;
		{
			int* const numRef1 = &num;
			//1) int 타입 데이터를 가리키는 const pointer
			//초기화 이후 다른 주소 값 대입 불가
			const int* numRef2 = &num;
			//2) const int 타입 데이타를 가리키는 포인터
			//*연산로 참조 값 변경이 불가
			const int* const numRef3 = &num;
			//3) const int 타입 데이타를 가리키는 const 포인터
			//1),2)속성을 다 가짐.
		}
		int anotherNum = 20;
		const int* ptr1 = &num;
		//*ptr1 = 5;//10->5, const int로 변경 불가, l-value화 됨
		ptr1 = &anotherNum;

		//int* const ptr2;//초기화 필요 error
		int* const ptr2 = nullptr;//nullptr초기화
		int* const ptr3 = &num;//초기화
		*ptr3 = 6;
		//ptr3 = &anotherNum;//const pointer로 대상 주소를 변경하지 못함

		unsigned int* pImg = new unsigned int[5] { 1, 2, 3, 4, 5 };
		std::cout << "buffer sum result : " << sum(pImg, 5) << std::endl;
		if (pImg != nullptr) {
			delete[]pImg; pImg = nullptr;
		}

	}
	int width = 5;
	int height = 5;
	unsigned int* pImg = new unsigned int[width * height] {
		//->col[0]...[4]
		3,4,5,6,2,//row[0]
		6,5,8,3,4,
		4,1,3,6,8,
		6,5,8,2,3,
		2,4,8,3,4,//row[4]
	};
	cout << "image data sum = " << sum(pImg, width * height) << endl;
	//partial data 추출
	//partial_sum 함수 start_index = 5, finish_index = 23
	int start_index = 6, finish_index = 23;
	cout << "image data sum = " 
		<< sum(pImg, width * height,start_index, finish_index) << endl;
	//partial_sum 함수 start_row,start_col (1,1), finish_row, finish_co (3,3)
	cout << "image data sum = "
		<< sum(pImg, width , height, 1,1,3,3) << endl;
	if (pImg != nullptr)delete[] pImg;
	return 0;
}