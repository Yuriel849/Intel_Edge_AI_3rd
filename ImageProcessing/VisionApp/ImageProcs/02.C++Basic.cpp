#include <iostream>

class Shape
{
public:
	Shape()
		:a(0) // member initialize; 객체 생성 시 초기화
		,b(10)
		, pA(nullptr)
	{
		// copy operator; 생성자 함수 호출 시 초기화
		a = 1;
		b = 2;
		std::cout << "Ctor" << std::endl;
	}
	~Shape();
private:
	int a, b;
	int* pA;
	// int a = 0, b = 1; // 이런식으로 초기화하는 것도 최신 C++에서는 지원하지만 기존에는 생성자에서 초기화하였다 (위에 생성자 확인하도록)
};

//#define CIRCLE 100; // 조사식에서는 값이 안 보이고 하나하나 관리하기가 번거롭다. 차라리 아래 상수가 좋다.
const size_t _CIRCLE = 100; // 조사식에 값이 보인다. 이보다 편리한 것이 아래 enum이다.

enum EShape { // 초기값 설정 안할 경우 0부터 1씩 증가하는 값을 가진다. 초기값을 설정할 경우, 그 초기값부터 1씩 증가하는 값을 가진다.
	eCircle,
	eRectangle = 200,
	eTriangle,
	ePoly,
	eShapeMax = 4
};

int main()
{
	// 아래 a와 b의 생성 과정의 차이는?
	// int 타입도 그 자체가 하나의 클래스이다.
	// 
	// int ctor->instance->|a|->operator '=' -> 1
	// a는 객체 생성 직후 초기값을 위한 메모리 공간을 마련해 놓지만 초기화를 하지 않는다. 대입연산자를 만난 후 '1'이라는 값을 a에 복사해 놓는다.
	int a = 1;
	// int ctor->instance + 2 (initialized)
	// b는 객체 생성과 동시에 '2'라는 값으로 초기화한다
	int b(2);
	char byChar = 'A'; // "캐릭터" 타입, "char" 타입이 아니다
	int c = a + b;
	std::cout << c << "\t=\t" << a << "\t+\t" << b << std::endl;

	int* pA = nullptr;
	std::cout << "size of pointer pA = " << sizeof(pA) << std::endl;

	EShape _eShape = EShape::eCircle;
	int* pShape = new int[EShape::eShapeMax];
	memset((void*)pShape, 0, sizeof(pShape) / sizeof(pShape[0])); // sizeof(pShape) = size of "int[EShape::eShapeMax]"
	memset((void*)pShape, 0, sizeof(int) * EShape::eShapeMax);
	
	if (pShape != nullptr) // pShape == nullptr에 사용하는 예외 발생
	{
		delete[] pShape; // "[]"는 pShape의 값이 배열이라는 의미
		pShape = nullptr;
	}
	return 1;
}