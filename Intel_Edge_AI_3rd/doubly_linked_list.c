#if 1

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int id;
	char data[255];

	struct node* next;
	struct node* prev;
} NODE;

typedef struct dll
{
	struct node* head;
	struct node* tail;
} DLL;

void init(struct dll* list);
void insert(DLL* list, int after_here, int new_id, char data[]);
struct node* find(DLL* list, int id);
void delete(DLL* list, int id);
void show_head_to_tail(DLL* list);
void show_tail_to_head(DLL* list);

int main(void)
{
	DLL* list = (DLL*)malloc(sizeof(DLL));

	init(list);

	insert(list, 1, 1, "A");
	insert(list, 1, 2, "C");
	insert(list, 2, 3, "E");
	insert(list, 3, 4, "G");
	insert(list, 4, 5, "I");
	show_head_to_tail(list);
	show_tail_to_head(list);

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

	return 0;
}

void init(struct dll* list)
{
	(*list).head = NULL;
	list->tail = NULL;
}

// 지정된 ID "after_here"를 가진 노드 다음에 추가하거나, 찾지 못할 경우 가장 마지막에 tail 다음에 추가한다.
void insert(DLL* list, int after_here, int new_id, char data[])
{
	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->id = new_id;
	new->data[0] = data[0]; // 코드 구현의 편의상 문자열의 첫 문자만 복사
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
			printf("got in");
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
	NODE* current = (NODE*)malloc(sizeof(NODE));
	current = list->head;
	while (current != NULL)
	{
		printf("%3d %c", current->id, current->data[0]);
		current = current->next;
	}
	printf("\n");
}

void show_tail_to_head(DLL* list)
{
	NODE* current = (NODE*)malloc(sizeof(NODE));
	current = list->tail;
	while (current != NULL)
	{
		printf("%3d %c", current->id, current->data[0]);
		current = current->prev;
	}
	printf("\n");
}

#endif