#include <iostream>

class Shape
{
public:
	Shape()
		:a(0) // member initialize; ��ü ���� �� �ʱ�ȭ
		,b(10)
		, pA(nullptr)
	{
		// copy operator; ������ �Լ� ȣ�� �� �ʱ�ȭ
		a = 1;
		b = 2;
		std::cout << "Ctor" << std::endl;
	}
	~Shape();
private:
	int a, b;
	int* pA;
	// int a = 0, b = 1; // �̷������� �ʱ�ȭ�ϴ� �͵� �ֽ� C++������ ���������� �������� �����ڿ��� �ʱ�ȭ�Ͽ��� (���� ������ Ȯ���ϵ���)
};

//#define CIRCLE 100; // ����Ŀ����� ���� �� ���̰� �ϳ��ϳ� �����ϱⰡ ���ŷӴ�. ���� �Ʒ� ����� ����.
const size_t _CIRCLE = 100; // ����Ŀ� ���� ���δ�. �̺��� ���� ���� �Ʒ� enum�̴�.

enum EShape { // �ʱⰪ ���� ���� ��� 0���� 1�� �����ϴ� ���� ������. �ʱⰪ�� ������ ���, �� �ʱⰪ���� 1�� �����ϴ� ���� ������.
	eCircle,
	eRectangle = 200,
	eTriangle,
	ePoly,
	eShapeMax = 4
};

int main()
{
	// �Ʒ� a�� b�� ���� ������ ���̴�?
	// int Ÿ�Ե� �� ��ü�� �ϳ��� Ŭ�����̴�.
	// 
	// int ctor->instance->|a|->operator '=' -> 1
	// a�� ��ü ���� ���� �ʱⰪ�� ���� �޸� ������ ������ ������ �ʱ�ȭ�� ���� �ʴ´�. ���Կ����ڸ� ���� �� '1'�̶�� ���� a�� ������ ���´�.
	int a = 1;
	// int ctor->instance + 2 (initialized)
	// b�� ��ü ������ ���ÿ� '2'��� ������ �ʱ�ȭ�Ѵ�
	int b(2);
	char byChar = 'A'; // "ĳ����" Ÿ��, "char" Ÿ���� �ƴϴ�
	int c = a + b;
	std::cout << c << "\t=\t" << a << "\t+\t" << b << std::endl;

	int* pA = nullptr;
	std::cout << "size of pointer pA = " << sizeof(pA) << std::endl;

	EShape _eShape = EShape::eCircle;
	int* pShape = new int[EShape::eShapeMax];
	memset((void*)pShape, 0, sizeof(pShape) / sizeof(pShape[0])); // sizeof(pShape) = size of "int[EShape::eShapeMax]"
	memset((void*)pShape, 0, sizeof(int) * EShape::eShapeMax);
	
	if (pShape != nullptr) // pShape == nullptr�� ����ϴ� ���� �߻�
	{
		delete[] pShape; // "[]"�� pShape�� ���� �迭�̶�� �ǹ�
		pShape = nullptr;
	}
	return 1;
}