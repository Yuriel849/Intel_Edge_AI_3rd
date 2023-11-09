/* DebugEx.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
 * F9 to set a breakpoint
 * F5 to proceed from breakpoint to breakpoint
 * F10 to proceed step by step, line by line
 *
 * Watch: Start a debugging session then go to "Debug > Window > Watch (디버그 > 창 > 조사식)"
 *        to track the values of variables and expressions as the program runs.
 *
 */

#include <iostream>
using namespace std;
int main()
{
    int i = 0;
    int sum = 0;

    for (; i < 10; i++)
    {
        sum = sum + i;
    }

    cout << "합 = " << sum << "입니다\n";
}

