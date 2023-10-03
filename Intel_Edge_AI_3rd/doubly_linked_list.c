#if 0

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
	int id;

	struct node* next;
	struct node* prev;
} NODE;

typedef struct dll
{
	struct node* head;
	struct node* tail;
} DLL;

void init(struct dll* list);
void is_empty(DLL* list);
void insert(DLL* list, int after_here, int new_id);
struct node* find(DLL* list, int id);
void delete(DLL* list, int id);
void show_head_to_tail(DLL* list);
void show_tail_to_head(DLL* list);

int main(void)
{
#if 1
	// 모바일 뱅킹 앱에서 최근에 이체한 계좌번호 목록
	int i, selection, acct_num, order = 0; // order == 0이면 최신 순, order == 1이면 오래된 순
	const int MAX_NUMBER = 54321; // 계좌번호 최고값
	const int MIN_NUMBER = 12345; // 계좌번호 최소값

	DLL* acct_list = (DLL*)malloc(sizeof(DLL));
	
	init(acct_list);
	srand(time(NULL));

	for (i = 0; i < 20; i++)
	{
		insert(acct_list, i, (rand() % (MAX_NUMBER + 1 - MIN_NUMBER)) + MIN_NUMBER); // 랜덤으로 계좌번호 20개 생성
	}

	while (1) // 사용자가 종료할 때까지 무한 반복
	{
		selection = 0; // 사용자가 선택한 작업 초기화
		acct_num = 0; // 사용자가 입력한 계좌번호 초기화

		printf("\n==== 최근에 이체한 계좌번호 목록입니다. ====\n");
		if (order == 0)
		{
			printf("============== 최신 순입니다. ==============\n");
			show_head_to_tail(acct_list);
		}
		else
		{
			printf("============== 오래된 순입니다. ==============\n");
			show_tail_to_head(acct_list);
		}
		printf("============================================\n");
		printf("======= 수행할 작업을 선택해주세요. ========\n");
		printf("======== 1. 최신 순으로 정렬합니다. ========\n");
		printf("======= 2. 오래된 순으로 정렬합니다. =======\n");
		printf("===== 3. 새로운 계좌번호를 추가합니다. =====\n");
		printf("===== 4. 기록된 계좌번호를 삭제합니다. =====\n");
		printf("===== 5. 사용한 계좌번호를 검색합니다. =====\n");
		printf("============== 6. 종료합니다. ==============\n");
		scanf("%d", &selection);

		switch (selection)
		{
		case 1: show_head_to_tail(acct_list); order = 0; break;
		case 2: show_tail_to_head(acct_list); order = 1; break;
		case 3:
			printf("===== 새로운 계좌번호를 입력해주세요. ======\n");
			scanf("%d", &acct_num);
			if (order == 0)
			{
				insert(acct_list, -1, acct_num);
				show_head_to_tail(acct_list);
			}
			else
			{
				insert(acct_list, 0, acct_num);
				show_tail_to_head(acct_list);
			}
			break;
		case 4:
			printf("===== 삭제할 계좌번호를 입력해주세요. ======\n");
			scanf("%d", &acct_num);
			delete(acct_list, acct_num);
			break;
		case 5:
			printf("===== 검색할 계좌번호를 입력해주세요. ======\n");
			scanf("%d", &acct_num);
			NODE* node = find(acct_list, acct_num);
			if (node == NULL)
			{
				printf("> 존재하지 않는 계좌번호입니다.=============\n\n");
			}
			else
			{
				printf("> 찾았습니다 : %5d\n ==================\n\n", node->id);
			}
			break;
		case 6:
			exit(0);
		default:
			printf("다시 선택해주세요\n\n");
		}
	}
#endif

#if 0
	DLL* list = (DLL*)malloc(sizeof(DLL));

	init(list);
	is_empty(list);
	insert(list, 0, 1);
	insert(list, 1, 2);
	insert(list, 2, 3);
	insert(list, 3, 4);
	insert(list, 4, 5);
	show_head_to_tail(list);
	show_tail_to_head(list);
	is_empty(list);

	int id_to_find;
	printf("검색할 ID를 입력하세요 : ");
	scanf("%d", &id_to_find);
	NODE* find_node = find(list, id_to_find);
	if (find_node == NULL)
	{
		printf("존재하지 않는 노드입니다.\n");
	}
	else
	{
		printf("ID : %d 노드를 찾았습니다.\n", id_to_find);
	}

	int id_to_delete;
	printf("삭제할 ID를 입력하세요 : ");
	scanf("%d", &id_to_delete);
	delete(list, id_to_delete);
	show_head_to_tail(list);

	printf("다시 한번 확인해주세요.\n");
	show_head_to_tail(list);
	show_tail_to_head(list);
#endif

	return 0;
}

void init(struct dll* list)
{
	(*list).head = NULL;
	list->tail = NULL;
}

void is_empty(DLL* list)
{
	if ((list->head == NULL) && (list->tail == NULL))
	{
		printf("빈 리스트입니다.\n");
	}
	else
	{
		printf("빈 리스트가 아닙니다.\n");
	}
}

// 지정된 ID "after_here"를 가진 노드 다음에 추가하거나, 찾지 못할 경우 가장 마지막에 tail 다음에 추가한다.
void insert(DLL* list, int after_here, int new_id)
{
	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->id = new_id;
	new->next = NULL;
	new->prev = NULL;

	NODE* current = (NODE*)malloc(sizeof(NODE));
	current = list->head;

	// 만약 빈 리스트에 최초로 노드를 추가한다면...
	if (current == NULL)
	{
		list->head = new;
		list->tail = new;
		return;
	}

	while (current != NULL)
	{
		// 현재 노드가 마지막 노드일 경우, 바로 뒤에 새로운 노드를 추가한다.
		if (current == list->tail)
		{
			new->prev = current;
			new->next = NULL;
			current->next = new;
			list->tail = new;
			return;
		}
		// 일치하는 ID를 가진 노드를 찾았을 경우 그 다음 위치에 새로운 노드를 추가한다.
		else if (current->id == after_here)
		{
			new->prev = current;
			new->next = current->next;
			current->next = new;
			new->next->prev = new;
			return;
		}
		current = current->next;
	}
}

struct node* find(DLL* list, int id)
{
	NODE* current = (NODE*)malloc(sizeof(NODE));
	current = list->head;

	while (current != NULL)
	{
		if (current->id == id)
		{
			return current;
		}
		current = current->next;
	}

	// 디폴트로 NULL 반환
	return NULL;
}

void delete(DLL* list, int id)
{
	NODE* current = (NODE*)malloc(sizeof(NODE));
	current = find(list, id);
	
	if (current == NULL)
	{
		printf("찾으시는 노드가 존재하지 않습니다.\n");
	}
	else if (current == list->head)
	{
		printf("첫번째 노드를 삭제합니다.\n");
		list->head = current->next;
		current->next->prev = NULL;
		free(current);
	}
	else if (current == list->tail)
	{
		printf("마지막 노드를 삭제합니다.\n");
		list->tail = current->prev;
		current->prev->next = NULL;
		free(current);
	}
	else
	{
		printf("삭제합니다.\n");
		current->next->prev = current->prev;
		current->prev->next = current->next;
		free(current);
	}
	return;
}

void show_head_to_tail(DLL* list)
{
	int count = 0;
	NODE* current = (NODE*)malloc(sizeof(NODE));
	current = list->head;
	while (current != NULL)
	{
		printf("%3d : %15d\n", ++count, current->id);
		current = current->next;
	}
	printf("\n");
}

void show_tail_to_head(DLL* list)
{
	int count = 0;
	NODE* current = (NODE*)malloc(sizeof(NODE));
	current = list->tail;
	while (current != NULL)
	{
		printf("%3d : %15d\n", ++count, current->id);
		current = current->prev;
	}
	printf("\n");
}

#endif