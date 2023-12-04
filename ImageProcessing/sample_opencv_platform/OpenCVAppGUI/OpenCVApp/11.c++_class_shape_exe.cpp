#include "common.h"
#include "shape.h"
#include "circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Polygone.h"
int main()
{
	
	Circle* pCircle = new Circle();
	Triangle* pTriangle = new Triangle();
	Rectangle* pRectangle = new Rectangle();
	Polygone* pPolygone = new Polygone();

	pTriangle->SetVertexCnt(3);

	Shape* pShape[4] = { 
		dynamic_cast<Circle*>(pCircle) , 
		dynamic_cast<Triangle*>(pTriangle) ,
		dynamic_cast<Rectangle*>(pRectangle) ,
		dynamic_cast<Polygone*>(pPolygone)};

	for (size_t i = 0; i < 4; i++)
	{
		pShape[i]->ShowShapeInfo();
	}
	//pShape = pCircle;///Çü º¯È¯ ...
	/*pShape = dynamic_cast<Circle*>(pCircle);
	pShape->ShowShapeInfo();
	pShape = dynamic_cast<Triangle*>(pTriangle);
	pShape->ShowShapeInfo();
	pShape = dynamic_cast<Rectangle*>(pRectangle);
	pShape->ShowShapeInfo();
	pShape = dynamic_cast<Polygone*>(pPolygone);
	pShape->ShowShapeInfo();*/
	for (size_t i = 0; i < 4; i++)
	{
		delete pShape[i]; pShape[i] = nullptr;
	}
	//if (pCircle != nullptr) { delete pCircle; pCircle = nullptr; }
	return 1;
}