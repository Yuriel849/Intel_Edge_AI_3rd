#include <iostream>
#include <string>
//
using namespace std;
////
////struct Info {
////	string name;
////	int old;
////	string adress;
////};
////
////double sum(const double* const pData, int length)
////{
////	double _sum = 0.0;
////	for (size_t i = 0; i < length; i++)
////	{
////		_sum += pData[i];
////	}
////	return _sum;
////}
////
////int main()
////{
////	if (false)
////	{
////		//using namespace std;
////
////		//int sum(int* pDatas, int length)
////		//{
////		//	int _sum = 0;
////		//	for (size_t i = 0; i < length; i++) { _sum += pDatas[i]; }
////		//	return _sum;
////		//}
////		//class Base
////		//{
////		//public:
////		//	Base() { cout << "Base::Ctor" << endl; }
////		//	virtual ~Base() { cout << "Base::Dtor" << endl; }//소멸자...virtual 상속관계...
////		//	virtual void Show() { cout << "Base : " << _a << endl; }//virtual keyword 자식이 재정의를 한다.
////		//	//강제성 pure, 알아서 잘 해라...그냥 가상함수
////		//	//virtual void Show()=0;//순수가상함수, 강제성
////		//	//virtual void Show();	//가상함수,자율성
////		//	void SetValue(int a) { _a = a; }
////		//	int GetValue() { return _a; }
////		//private:
////		//	int _a = 0;
////		//};
////		//class Child : public Base
////		//{
////		//public:
////		//	Child() { cout << "Child::Ctor" << endl; }
////		//	~Child() { cout << "Child::Dtor" << endl; }
////		//	void Show() override { cout << "Derived : " << GetValue()/*of Base*/ << endl; }//of Child
////		//};
////		//int main()
////		//{
////		//	struct _datas
////		//	{
////		//		int a; double b; char c; std::string str; //auto i = 10;//for
////		//	};
////		//	class _cDatas
////		//	{
////		//	public:
////		//		_cDatas() { cout << "Ctor" << endl; }
////		//		~_cDatas() { cout << "Dtor" << endl; }
////		//	private:
////		//	protected:
////		//	};
////		//	//DATA TYPES
////		//	if (true)
////		//	{
////		//		int a; double b; char c; std::string str; auto i = 10;//for
////		//		cout << "Hello World" << endl;
////		//		cin >> a;//a라는 변수에 입력을 한다.
////
////		//		_datas datas;
////
////		//		_cDatas cData;
////		//	}
////
////		//	//dynamically memory allocation
////		//	int* pData = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
////		//	_datas* pstData = new _datas();
////		//	_cDatas* pCData = new _cDatas();
////
////		//	//cout << "int datas sum  = " << sum(pData, 10) << endl;
////		//	cout << "int datas sum  = " << sum(pData, 10) << endl;
////
////		//	//free
////		//	if (pData != nullptr) { delete[] pData; pData = nullptr; }
////		//	if (pstData != nullptr) { delete pstData; pstData = nullptr; }
////		//	if (pCData != nullptr) { delete pCData; pCData = nullptr; }
////
////		//	//c++ 장점 : 추상화, 은닉성, 상속성, 다형성
////		//	//추상화..일반화...virtual
////		//	//public, private, protected
////		//	//상속성.. Parent...Derived class....
////		//	//다형성...Parent...Derived class ...using virtual keyword 접근... up-casting{dynamic_cast<부모*>}
////		//	//         static_cast / const_cast / reinterpret_cast / dynamic_cast
////		//	//........virtual key....pure virtual function() ...interface 설계
////		//	//........virtual + __vfptr using virtual function table 저장됨
////		//	//.................부모 클래스의 자원을 관리함
////		//	Base base;
////		//	Child child;
////		//	Base* pBase = new Base();
////		//	Child* pChild = new Child();
////		//	pBase->SetValue(10);//public but private _a ?? access(X)
////		//	pBase->Show();
////
////		//	pChild->SetValue(20);
////		//	pChild->Show();
////		//	if (pBase != nullptr) { delete pBase; pBase = nullptr; }
////		//	if (pChild != nullptr) { delete pChild; pChild = nullptr; }
////		//	return 1;
////		//}
////
////
////
////	}
////	if (0) {
////		string name, link;
////		int age;
////		cout << "이름 : ";
////		cin >> name;
////		cout << "나이 : ";
////		cin >> age;
////		cout << "Link URL : ";
////		cin >> link;
////		cout << "\"" << link << "\"";
////	}
////	if (0)
////	{
////		double* pData = new double[20]();//
////		//{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
////		for (int i = 0; i < 20; i++) pData[i] = i + 1;
////		cout << "배열의 총합 : " << sum(pData, 20);
////		if (pData != nullptr)
////		{
////			delete [] pData;
////			pData = nullptr;
////		}
////	}
////
////}
////
////	
//
//#include <iostream>
//#include <string>
//
//using namespace std;
//class Base
//{
//public:
//	Base() {}
//	virtual ~Base() {}
//	virtual void Show() = 0;
//};
//
//class ChildA : public Base
//{
//public:
//	ChildA() {}
//	~ChildA() {}
//	void Show() { cout << "ChildA" << endl; }
//
//private:
//
//};
//
//class ChildB : public Base
//{
//public:
//	ChildB() {}
//	~ChildB() {}
//	void Show() { cout << "ChildB" << endl; }
//
//private:
//
//};
//
//int main()
//{
//	Base* pBase = dynamic_cast<Base*>(new ChildA);
//	pBase->Show();
//	if (pBase != nullptr)
//	{
//		delete pBase;
//		pBase = nullptr;
//	}
//
//	pBase = dynamic_cast<Base*>(new ChildB);
//	pBase->Show();
//
//	if (pBase != nullptr)
//	{
//		delete pBase;
//		pBase = nullptr;
//	}
//
//	return 1;
//}

#include <iostream>
#include <string>

using namespace std;
class IShape
{
public:
	IShape() { cout << "IShape::Ctor" << endl; }
	virtual ~IShape() { cout << "IShape::Dtor" << endl; }
	virtual int GetShape() = 0; //circle-1, rect-2
private:

};

class Circle :public IShape
{
public:
	Circle() { cout << "Circle::Ctor" << endl; }
	~Circle() { cout << "Circle::Dtor" << endl; }
	int GetShape() override { return 1; }
};

class Rect : public IShape
{
public:
	Rect() { cout << "Rect::Ctor" << endl; }
	~Rect() { cout << "Rect::Dtor" << endl; }
	int GetShape() override { return 2; }
};

int main()
{
	Circle* pCircle = new Circle;
	Rect* pRect = new Rect;
	IShape* pIShape[2] = {
		dynamic_cast<Circle*>(pCircle),
		dynamic_cast<Rect*>(pRect),
	};
	for (size_t i = 0; i < 2; i++)
	{
		cout << pIShape[i]->GetShape() << endl;
	}

	for (size_t i = 0; i < 2; i++)
	{
		if (pIShape[i] != nullptr)
		{
			delete pIShape[i];
			pIShape[i] = nullptr;
		}
	}

	return 1;
}