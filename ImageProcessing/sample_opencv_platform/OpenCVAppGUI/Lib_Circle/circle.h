#pragma once

#include <string>
#include <iostream>

//#define DLL_EXPORTS

#ifdef DLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif

//#include "common.h"
#include "../OpenCVApp/shape.h"

class DLL_DECLSPEC Circle : public Shape//상속관계
{
public:
	Circle();
	~Circle();
	void ShowShapeInfo();
protected:
private:
};

extern "C"
{
	DLL_DECLSPEC Shape* lib_Circle_Create();
	DLL_DECLSPEC void lib_Circle_Release(Shape* obj);
}