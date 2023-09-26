#if 1

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
void add(DLL* list, int id, char data[]);
struct node* find(DLL* list, int id);
void delete(DLL* list, int id);
void show_head_to_tail(DLL* list);
void show_tail_to_head(DLL* list);


int main(void)
{
	return 0;
}

void init(struct dll* list)
{
	(*list).head = NULL;
	list->tail = NULL;
}

void add(DLL* list, int id, char data[])
{
	NODE* new = (NODE*)malloc(sizeof(NODE));
	(*new).id = id;
	new->data[0] = data[0]; // 코드 구현의 편의상 문자열의 첫 문자만 복사
	new->next = NULL;
	new->prev = NULL;

	// 만약 빈 리스트에 최초로 노드를 추가한다면...
	if (list->head == NULL)
	{
		list->head = new;
		list->tail = new;
		return;
	}
	// 빈 리스트가 아닐 경우...
	else
	{
		list->tail->next = new;
		new->prev = list->tail;
		list->tail = new;
		return;
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
		printf("찾으시는 노드가 존재하지 않습니다.");
	}
	else if (current == list->head)
	{
		printf("첫번째 노드를 삭제합니다.");
		list->head = current->next;
		current->next->prev = NULL;
		free(current);
	}
	else if (current == list->tail)
	{
		printf("마지막 노드를 삭제합니다.");
		list->tail = current->prev;
		current->prev->next = NULL;
		free(current);
	}
	else
	{
		printf("삭제합니다.");
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