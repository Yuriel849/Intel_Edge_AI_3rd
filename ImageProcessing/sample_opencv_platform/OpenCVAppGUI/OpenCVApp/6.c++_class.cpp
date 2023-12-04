#include <iostream>
#include <string>
#include <vector>

//class
//...object(객체).....
//소프트웨어 시스템을 나누는 단위
//특성(상태)와 행위를 가지는 어떤한 실체
//상태 : 내부변수
//행위 : 함수
//ex)자동차
//특성(상태) : 차체, 엔진, 스티어링휠, 변속기, 바퀴..
//행위 : 한다{직진, 좌회전, 우회전, 정지..가속}
//객체간의 소통
//자동차를 운전하기 위해 명령을 보낸 상대 객체가 있어야 함
//운전자... 운전자(주체).->.자동차(객체)...메시지 보냄

//클래스(class)
//유사한 특성(상태)와 행위를 갖는 객체를 표현하는 모형(틀)
//관념을 표현한다....추상화(abstration)
//객체의 추상화가 ... class
//모든 객체는 클래스를 기반으로 생성되며 
//그 객체를 클래스의 인스턴스(instance)라고 합니다.

class Car//class  [클래스 이름]
{		//scope 시작
public:	//접근지정자...public/protected/private
	Car();//생성자...Creator...Ctor
	~Car();//소멸자..Destory...Dtor
	void setMomey(int kw) { momey = kw; }
	int getMomey() { return momey; }
protected:
private://접근지정자...public/protected/private
	int momey;
};		//scope 끝



class BMW : public Car//상속성
{

};
//High-Level Programming ... c++
//객체지향 언어
//추상화(Abstration)...일반화
// ...휴대폰..전화를 받고/걸고
// 정보은닉의 수단중 하나로 공통의 속성이나 기능을 묶어서 클래스로 정의한것
//캡슐화(EnCapsulation)
// ...실제로 구현 및 동작되는 부분에 대해 데이터를 처리함에 있어
//    객체의 데이터를 직접 접근할 수 없고..메소드(method)를 통해서만 가능
//상속성(Inheritance)
// ...기존 클래스를 확장한 파생 클래스를 정의하는 것
// ...iphone3s...iphone15...기본기능+확장된 개념으로 파생
//다형성(Polymorphism)★★★★★★★★★★★★
//..."오버라이딩"...재정의...다양한 형태로 나타날 수 있는 특징
//   음성인식 기능->아이폰..시리 호출...갤럭시..빅스비 호출
//   call()..Number...->음성
