#if 0

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void convert_decimal_to_binary(char* binary, int decimal);
void print(char* binary);

int main(void)
{
	int a, b, AND_result, OR_result, XOR_result, r_shift_result, l_shift_result, NOR_result_a, NOR_result_b;
	char binary_a[32] = { 0 }, binary_b[32] = { 0 };
	char binary_AND[32] = { 0 }, binary_OR[32] = { 0 }, binary_XOR[32] = { 0 };
	char binary_r_shift[32] = { 0 }, binary_l_shift[32] = { 0 }, binary_NOR_a[32] = { 1 }, binary_NOR_b[32] = { 1 };

	printf("비트연산을 수행할 두 개의 정수를 입력하세요. >> ");
	scanf("%d %d", &a, &b);

	AND_result = a & b;
	OR_result = a | b;
	XOR_result = a ^ b;
	r_shift_result = a >> b;
	l_shift_result = a << b;
	NOR_result_a = ~a;
	NOR_result_b = ~b;

	convert_decimal_to_binary(binary_a, a);
	convert_decimal_to_binary(binary_b, b);
	convert_decimal_to_binary(binary_AND, AND_result);
	convert_decimal_to_binary(binary_OR, OR_result);
	convert_decimal_to_binary(binary_XOR, XOR_result);
	convert_decimal_to_binary(binary_r_shift, r_shift_result);
	convert_decimal_to_binary(binary_l_shift, l_shift_result);
	convert_decimal_to_binary(binary_NOR_a, NOR_result_a);
	convert_decimal_to_binary(binary_NOR_b, NOR_result_b);

	printf("%14d : ", a);
	print(binary_a);
	printf("%14d : ", b);
	print(binary_b);
	printf("%d & %d = %d : ", a, b, AND_result);
	print(binary_AND);
	printf("%d | %d = %d : ", a, b, OR_result);
	print(binary_OR);
	printf("%d ^ %d = %d : ", a, b, XOR_result);
	print(binary_XOR);
	printf("%d >> %d = %d: ", a, b, r_shift_result);
	print(binary_r_shift);
	printf("%d << %d = %d: ", a, b, l_shift_result);
	print(binary_l_shift);
	printf("~%5d = %5d : ", a, NOR_result_a);
	print(binary_NOR_a);
	printf("~%5d = %5d : ", b, NOR_result_b);
	print(binary_NOR_b);

	return 0;
}

void convert_decimal_to_binary(char* binary, int decimal)
{
	int count = 0;

	while (decimal > 0)
	{
		*(binary + count++) = decimal % 2;
		decimal /= 2;
	}
}

void print(char* binary)
{
	int i = 0;

	for (i = 31; i > -1; i--)
	{
		printf("%d", *(binary+i));
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
	printf("\n");
}

#endif