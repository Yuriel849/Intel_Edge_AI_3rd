#include <iostream>
int main()
{
	const int maxLength = 5 * 5;
	int data[maxLength] = {
		1,2,3,4,5,
		1,0,2,0,4,
		2,3,0,2,3,
		3,1,2,3,2,
		1,2,3,0,2 };
	//data {0~5}:6
	//8bit img {0~255}:256
	//16bit img {0~65534}:65535
	const int histo_max = 6;//from data[]:0~5
	int histo[histo_max] = { 0, };

	//histo[0] = 0, 0, 0, 0;//4     //from data[?] = 0
	// histo[0]++;->4
	//... 0 ~ 5
	//histo[3] = 3,3,3, 3, 3, 3//6
	//histo[5]

	for (size_t i = 0; i < maxLength; i++) histo[data[i]]++;

	for (size_t row = 0; row < histo_max; row++)
	{
		std::cout << row << "|";
		for (size_t col = 0; col < histo[row]; col++)
		{
			std::cout << "=";
		}
		std::cout << std::endl;
	}
	int a = 0;
	//Histogram을 출력하세요
	//0-4
	//1-?
	//..
	//5-1

	//0 | ====
	//1 | ?
	//..
	//5 | =
}