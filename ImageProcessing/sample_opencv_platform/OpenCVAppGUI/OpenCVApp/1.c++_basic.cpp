
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//void main()
#define AAA "aaa"
#define PI 3.14
int main()
{
    //상수변수
    const char* const_AAA = "aaa";
    const float const_PI = 3.14;
    int a1 = 10;
    //10 = a1;
    //BOOL babc = TRUE;
    const bool bComp = false;
    const int const_int = 100;
    const short const_short = 0xfff;
    const std::string const_str = "abcd";
    std::string str_a = "a";
    std::string str_b = "b";
    string str_c = "c";
    string str_d = "d";
    string str_e = "e";
    
    int a = 0;  int b(0);
    std::cout << "Hello World!\n";
    int img1 = 0;
    int img2 = 0;
    int img3 = 0;
    int img4 = 0;
    int img5 = 0;
    //배열
    int arrimg[25] = {0,};
    arrimg[5] = 5;
    arrimg[6] = 6;
    arrimg[7] = 7;
    arrimg[8] = 8;
    //벡터
    std::vector<int> vimg(5);

    int sz_int = sizeof(int);
    //캐스팅
    //static_cast
    //const_cast
    //reinterpret_cast
    //dynamic_cast
    float f_data = 1.23;
    int n_data = (int)f_data;//c_style
    n_data = static_cast<int>(f_data);//c++_style
    //f_data
    //??=(int)f_data;//임시객체생성과소멸
    //n_data = ??

    const char const_string[] = "ABC";
    std::cout << const_string << std::endl;
    char* msg = const_cast<char*>(const_string);
    msg[0] = 'D';
    std::cout << const_string << std::endl;
    std::cout << msg <<std::endl;
    
    //static_cast
    char cNum = 'a';
    int* pNum = nullptr;
    pNum = (int*)(&cNum);//c-style
    //pNum = static_cast<int*>(&cNum);//c++
    *pNum = 5;
    return 0;//int 반환
}
