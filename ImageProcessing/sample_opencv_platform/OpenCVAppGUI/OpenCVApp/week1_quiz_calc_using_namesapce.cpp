//Quiz
//namespace를 이용하여 사칙연산 계산기를 만들어 봅니다.
//두 수 a,b 입력을 받습니다.
//계산할 기호 +,-,/,* 입력을 받습니다.
//namespace Calc{} 선언합니다.
//Calc 네이스페이스에는 add(*),sub(-), mul(*), div(/) 함수를 만들어요
// 함수 잘 모르겠어요?...잠시만 기다려봅니다.일단 만들어봐요
// main도 함수입니다.
//입력과 출력은 cin, cout을 사용합니다.

//예제 형태
Calc Program Started
input 1 - 10
input 2 - 20
input symbol - *
result => 10 * 20 = 200
너무 잘해서 ... 함수 호출 되는 부분을 업그레이드 해봅니다.
result 함수를 호출해서 결과를 출력해봅니다
여러분들 add/sub/mul/div 너무 많이 타이핑하고 있죠?

hint
namespace Calc
{
	int a=0, b=0, resVal=0;
	char symbol=' ';
	int result()
	{
		resVale = 0;
		if (symbol == '+') resValue = add(a, b);
		else if (symbol == '-') resValue = sub(a, b);
		else if (symbol == '*') resValue = mul(a, b);
		else if (symbol == '/') resValue = div(a, b);
		return resVal;
	}



	int add(int a, b) { return a + b; }
	int sub(int a, b) { return a - b; }
	int mul(int a, b) { return a * b; }
	int div(int a, b) { return a / b; }
	//...
}
//using namespace Calc;





























































































































int main()
{
	//Set Calc variables
	//Call Calc result
	std::cout << "input 1 : "; std::cin >> Calc::a;
	std::cout << "input 2 : "; std::cin >> Calc::b;
	std::cout << "input S : "; std::cin >> Calc::symbol;
	std::cout << "result : " << Calc::result();



}