
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int sum = 10;
    if (sum > 10)
        cout << "sum > 10" << endl;
    else if (sum > 5)//if (sum > 5)
        cout << "sum > 5" << endl;
    else
        cout << "no result" << endl;

    //Quiz
    //학점을 출력하세요
    //정수타입 변수 Score가 100보다 같거나 클 때, A
    //정수타입 변수 Score가 100보다 작고 90보다 같거나 클 때, B
    //정수타입 변수 Score가 90보다 작고 80보다 같거나 클 때, C
    //그외, None
    //로 출력되는 조건문 코드를 작성하세요.
    int score = 100;
    //if (score >= 80 && score <90)cout << "C" << endl;
    if (score >= 80)
    {
        if (score < 90)cout << "C" << endl;
    }
    else if (score >= 90)cout << "B" << endl;
    else if (score >= 100)cout << "A" << endl;
    else cout << "None" << endl;

    /*if (score >= 100)cout << "A" << endl;
    else if (score >= 90)cout << "B" << endl;
    else if (score >= 80)cout << "C" << endl;
    else cout << "None" << endl;*/


    //반복문
    int rows = 10;
    int cols = 10;
    for (int row = 0; row < rows; row++)
    {
        cout << "row=" << row << "\t";
        for (int col = 0; col < cols; col++)
        {
            cout << "col=" << col << "\t";
        }
        cout << endl;
    }
    //pointer, reference
    //메모리 주소를 의미하는 곳을 저장하는 형태의 변수
    //장 : 배열과 같은 연속 데이터에 접근+조작이 용이
    //메모리 동적 할당/해제 리소스 관리 가능-효율성
    //복잡한 자료 구조 효율적으로 접근 가능 및 처리
    //[int*] [pData] = nullptr;
    int Data = 100;
    int* pData = &Data; //pData = nullptr;
    
    int nArray[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int*     pArray = nArray;//&nArray[0]
    for (int i = 0; i < sizeof(nArray) / sizeof(nArray[0]); i++)
    {
        cout << *(pArray + i) << "\t";
        cout << pArray[i] << "\t";
        cout << *(pArray++) << "\t";
    }
    
    
    










    return 0;
}
