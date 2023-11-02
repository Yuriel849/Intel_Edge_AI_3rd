#include <iostream>
using namespace std;
class IShape//named
{
public:
    IShape() { cout << "IShape::Ctor" << endl; }
    ~IShape() { cout << "IShape::Dtor" << endl; }
    virtual void DisplayShapeInfo() = 0; // 순수가상함수; 구현하지 않는 이상 객체 생성 불가
    void SetShape(int& shapeinfo) { _ShapeInfo = shapeinfo; }
    //int SetShape(int shapeinfo) { _ShapeInfo = shapeinfo; }
    int GetShape() { return _ShapeInfo; }
private:
    int _ShapeInfo = 0;//0 - circle, 1 - rect, 2 - triangle
};

class ShapeRect : public IShape
{
public:
    ShapeRect() { cout << "ShapeRect::Ctor" << endl; }
    ~ShapeRect() { cout << "ShapeRect::Dtor" << endl; }
    void DisplayShapeInfo() override { cout << "This is Rectangle" << endl; }
};

int main()
{
    {
        ShapeRect sRect;//instance
        IShape* shape = nullptr; //object-pointer = nullptr; 포인터 초기화에 사용, "nullptr" 자체가 하나의 타입
        shape = dynamic_cast<IShape*>(&sRect);
        int shapeInfo = 100;
        shape->SetShape(shapeInfo);
        shapeInfo = shape->GetShape();
        shape->DisplayShapeInfo();
    }

    return 1;
}
