/*
	전달인자를 받아 반환인자로 리턴하는 함수를 활용할 것.
	for, if, while 문 등을 반드시 사용할 것. (단순 printf 금지).
	단순 조건문 반복은 인정하지 않음.
	주어진 조건을 모두 만족해야 함.

	3. 경로 설정
	맵 정보는 현재의 위치에서 갈 수 있는 경로를 나타내 주어야 한다.
	주어진 5x5 미로에서 임의의 좌표를 입력했을 때, 해당 좌표에서 벽을 만나기 전까지 직선으로 가장 많이 갈 수 있는 방향 및 이동 경로를 출력하라.
	- 입력한 좌표가 벽이라면 벽이라고 출력되게 하시오.
	- 갈 수 있는 경로의 칸수가 동일하다면 둘 다 출력 되게 하시오.
	예) (4,5) 입력 시 경로 '하', (3,5)->(2,5)->(1,5) 출력
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
	// 미로를 5x5크기의 2차원 배열에 저장 (0이면 빈공간, 1이면 벽, 왼쪽 위 꼭지점이 (x=0,y=0))
	int map[MAX_ROW][MAX_COL] =
	{
		{ 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 0 },
		{ 0, 1, 1, 1, 0 },
	};
	int row = 0, col = 0;
	int up = -1, down = -1, left = -1, right = -1; // 상하좌우로 이동가능한 경로의 길이 저장
    int max = 0;
	
	// 사용자 입력을 받아서 좌표를 설정
	printf("좌표를 입력해주세요... 형식은 \"(4,5)\"으로 입력해주세요 : ");
	scanf("(%d,%d)", &row, &col);
	printf("\n입력한 좌표는 (%d,%d)입니다.\n", row, col);

	// 사용자 지정 좌표가 유효한 좌표인지 확인, row, col 두 값 모두 확인
	if (!is_valid(row - 1) || !is_valid(col - 1))
	{
		printf("제시하신 좌표는 사용할 수 없는 값입니다.\n1~5 사이의 값을 좌표로 입력해주세요.\n종료합니다\n");
		return;
	}

	// 사용자 지정 좌표가 벽인지 확인
	if (is_wall(map, row-1, col-1))
	{
		printf("제시하신 좌표는 벽 속입니다.\n여기서는 시작할 수 없습니다.\n종료합니다.\n");
		return;
	}

    // 경로의 최대 길이 구하기
    max = find_longest(up, down, left, right);

	// 상하좌우 4방향을 모두 확인하여 벽을 만나기 전까지 이동할 수 있는 거리와 좌표를 확인
	find_way(map, row-1, col-1, &up, &down, &left, &right);
}
#endif

// 사용자 지정 좌표가 벽인지 확인하고 벽이면 1 반환, 벽이 아니라면 0 반환
int is_wall(int map[MAX_ROW][MAX_COL], int row, int col)
{
	if (*(*(map + row) + col))
	{
		return 1;
	}
	return 0;
}

// 사용자 지정 좌표가 유요한 값인지 확인하고 1~5 사이의 값이면 1 반환, 아니라면 0 반환
int is_valid(int val)
{
	if (0 < val && val < 6)
	{
		return 1;
	}
	return 0;
}

// 미로 길찾기
void find_way(int map[MAX_ROW][MAX_COL], int row, int col, int *up, int *down, int *left, int *right)
{
    int row_cnt = row, col_cnt = col;
	
    // 상
    // up 이동 가능 값
	while (!map[row_cnt][col] && row_cnt >= 0)
	{
		(*up)++;
		row_cnt--;
	};
    row_cnt = row; // 초기화

    // 하
    // down 이동 가능 값
    while (!map[row_cnt][col] && row_cnt < MAX_ROW)
    {
		(*down)++;
        row_cnt++;
    }

    // 좌
    // left 이동 가능 값
    while (!map[row][col_cnt] && col_cnt >= 0)
    {
		(*left)++;
        col_cnt--;
    }

    col_cnt = col; // 초기화

    // 우
    // right 이동 가능 값
    while (!map[row][col_cnt] && col_cnt < MAX_COL)
    {
		(*right)++;
        col_cnt++;
    }
}

// 경로의 최대 길이 구하기
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

    // 최대값 출력
    int i;
    printf("\n---최대값 출력---\n");

    if (max == *up)
    {
        printf("'하', ");
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
        printf("'상', ");
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
        printf("'좌', ");
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
        printf("'우', ");
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