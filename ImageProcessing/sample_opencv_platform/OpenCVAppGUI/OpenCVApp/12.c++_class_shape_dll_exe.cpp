#include <Windows.h>
#include <iostream>
//#include "../Lib_Circle/circle.h"//"../Lib_Circle/circle.h"
#include "../Lib_Triangle/Triangle.h"//"../Lib_Triangle/Triangle.h"
//#include "../Lib_Rectangle/rectangle.h"
#ifdef _DEBUG
#pragma comment(lib,"Lib_Triangled.lib")
#else	//RELEASE
#pragma comment(lib,"Lib_Triangle.lib")
#endif

typedef Shape* (*fpncreate)();
typedef void(*fpnRelease)(Shape* obj);

int main()
{
	Shape* pShape = nullptr;
	bool dynamic_loading_dll = true;
	if(dynamic_loading_dll)
	{
		HINSTANCE hModule = LoadLibrary("Lib_Triangled.dll");
		if (hModule != NULL)
		{
			fpncreate _fpcreate = (fpncreate)GetProcAddress(hModule, "lib_Triangle_Create");
			if (_fpcreate)
			{
				//Shape* pShape = new Circle();
				pShape = dynamic_cast<Triangle*>(_fpcreate());
			}

			pShape->ShowShapeInfo();

			fpnRelease _fpRelease = (fpnRelease)GetProcAddress(hModule, "lib_Triangle_Release");
			if (_fpRelease)
			{
				_fpRelease(pShape);
			}
			FreeLibrary(hModule);
		}
	}
	//else
	//{
	//	Shape* pShape = new Circle();
	//	pShape->ShowShapeInfo();
	//	if (pShape != nullptr)
	//	{
	//		delete pShape; pShape = nullptr;
	//	}


	//}
	
	
	return 1;
}