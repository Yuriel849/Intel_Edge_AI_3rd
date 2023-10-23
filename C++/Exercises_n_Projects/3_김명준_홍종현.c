/*
	�������ڸ� �޾� ��ȯ���ڷ� �����ϴ� �Լ��� Ȱ���� ��.
	for, if, while �� ���� �ݵ�� ����� ��. (�ܼ� printf ����).
	�ܼ� ���ǹ� �ݺ��� �������� ����.
	�־��� ������ ��� �����ؾ� ��.

	3. ��� ����
	�� ������ ������ ��ġ���� �� �� �ִ� ��θ� ��Ÿ�� �־�� �Ѵ�.
	�־��� 5x5 �̷ο��� ������ ��ǥ�� �Է����� ��, �ش� ��ǥ���� ���� ������ ������ �������� ���� ���� �� �� �ִ� ���� �� �̵� ��θ� ����϶�.
	- �Է��� ��ǥ�� ���̶�� ���̶�� ��µǰ� �Ͻÿ�.
	- �� �� �ִ� ����� ĭ���� �����ϴٸ� �� �� ��� �ǰ� �Ͻÿ�.
	��) (4,5) �Է� �� ��� '��', (3,5)->(2,5)->(1,5) ���
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int is_wall(int map[MAX_ROW][MAX_COL], int row, int col);
int is_valid(int val);
void find_way(int map[MAX_ROW][MAX_COL], int row, int col, int* up, int* down, int* left, int* right);

#if 0
void main(void)
{
	// �̷θ� 5x5ũ���� 2���� �迭�� ���� (0�̸� �����, 1�̸� ��, ���� �� �������� (x=0,y=0))
	int map[MAX_ROW][MAX_COL] =
	{
		{ 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 0 },
		{ 0, 1, 1, 1, 0 },
	};
	int row = 0, col = 0;
	int up = -1, down = -1, left = -1, right = -1; // �����¿�� �̵������� ����� ���� ����
    int max = 0;
	
	// ����� �Է��� �޾Ƽ� ��ǥ�� ����
	printf("��ǥ�� �Է����ּ���... ������ \"(4,5)\"���� �Է����ּ��� : ");
	scanf("(%d,%d)", &row, &col);
	printf("\n�Է��� ��ǥ�� (%d,%d)�Դϴ�.\n", row, col);

	// ����� ���� ��ǥ�� ��ȿ�� ��ǥ���� Ȯ��, row, col �� �� ��� Ȯ��
	if (!is_valid(row - 1) || !is_valid(col - 1))
	{
		printf("�����Ͻ� ��ǥ�� ����� �� ���� ���Դϴ�.\n1~5 ������ ���� ��ǥ�� �Է����ּ���.\n�����մϴ�\n");
		return;
	}

	// ����� ���� ��ǥ�� ������ Ȯ��
	if (is_wall(map, row-1, col-1))
	{
		printf("�����Ͻ� ��ǥ�� �� ���Դϴ�.\n���⼭�� ������ �� �����ϴ�.\n�����մϴ�.\n");
		return;
	}

    // ����� �ִ� ���� ���ϱ�
    max = find_longest(up, down, left, right);

	// �����¿� 4������ ��� Ȯ���Ͽ� ���� ������ ������ �̵��� �� �ִ� �Ÿ��� ��ǥ�� Ȯ��
	find_way(map, row-1, col-1, &up, &down, &left, &right);
}
#endif

// ����� ���� ��ǥ�� ������ Ȯ���ϰ� ���̸� 1 ��ȯ, ���� �ƴ϶�� 0 ��ȯ
int is_wall(int map[MAX_ROW][MAX_COL], int row, int col)
{
	if (*(*(map + row) + col))
	{
		return 1;
	}
	return 0;
}

// ����� ���� ��ǥ�� ������ ������ Ȯ���ϰ� 1~5 ������ ���̸� 1 ��ȯ, �ƴ϶�� 0 ��ȯ
int is_valid(int val)
{
	if (0 < val && val < 6)
	{
		return 1;
	}
	return 0;
}

// �̷� ��ã��
void find_way(int map[MAX_ROW][MAX_COL], int row, int col, int *up, int *down, int *left, int *right)
{
    int row_cnt = row, col_cnt = col;
	
    // ��
    // up �̵� ���� ��
	while (!map[row_cnt][col] && row_cnt >= 0)
	{
		(*up)++;
		row_cnt--;
	};
    row_cnt = row; // �ʱ�ȭ

    // ��
    // down �̵� ���� ��
    while (!map[row_cnt][col] && row_cnt < MAX_ROW)
    {
		(*down)++;
        row_cnt++;
    }

    // ��
    // left �̵� ���� ��
    while (!map[row][col_cnt] && col_cnt >= 0)
    {
		(*left)++;
        col_cnt--;
    }

    col_cnt = col; // �ʱ�ȭ

    // ��
    // right �̵� ���� ��
    while (!map[row][col_cnt] && col_cnt < MAX_COL)
    {
		(*right)++;
        col_cnt++;
    }
}

// ����� �ִ� ���� ���ϱ�
int find_longest(int up, int down, int left, int right)
{
    int max = 0;
    
    if (max < up)
    {
        max = up;
    }
    if (max < down)
    {
        max = down;
    }
    if (max < left)
    {
        max = left;
    }
    if (max < right)
    {
        max = right;
    }

    return max;
}

/*

    // �ִ밪 ���
    int i;
    printf("\n---�ִ밪 ���---\n");

    if (max == *up)
    {
        printf("'��', ");
        for (i = 1; i <= *up; i++)
        {
            if (i != 1)
            {
                printf("->");
            }
            printf("(%d, %d)", row - i + 1, col + 1);
        }
        printf("\n");
    }
    if (max == *down)
    {
        printf("'��', ");
        for (i = 1; i <= *down; i++)
        {
            if (i != 1)
            {
                printf("->");
            }
            printf("(%d, %d)", row + i + 1, col + 1);
        }
        printf("\n");
    }
    if (max == *left)
    {
        printf("'��', ");
        for (i = 1; i <= *left; i++)
        {
            if (i != 1)
            {
                printf("->");
            }
            printf("(%d, %d)", row + 1, col - i + 1);
        }
        printf("\n");
    }
    if (max == *right)
    {
        printf("'��', ");
        for (i = 1; i <= *right; i++)
        {
            if (i != 1)
            {
                printf("->");
            }
            printf("(%d, %d)", row + 1, col + i + 1);
        }
        printf("\n");
    }
    printf("\n");
*/