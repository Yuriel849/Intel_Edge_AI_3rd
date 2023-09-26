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
	new->data[0] = data[0]; // �ڵ� ������ ���ǻ� ���ڿ��� ù ���ڸ� ����
	new->next = NULL;
	new->prev = NULL;

	// ���� �� ����Ʈ�� ���ʷ� ��带 �߰��Ѵٸ�...
	if (list->head == NULL)
	{
		list->head = new;
		list->tail = new;
		return;
	}
	// �� ����Ʈ�� �ƴ� ���...
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

	// ����Ʈ�� NULL ��ȯ
	return NULL;
}

void delete(DLL* list, int id)
{
	NODE* current = (NODE*)malloc(sizeof(NODE));
	current = find(list, id);
	
	if (current == NULL)
	{
		printf("ã���ô� ��尡 �������� �ʽ��ϴ�.");
	}
	else if (current == list->head)
	{
		printf("ù��° ��带 �����մϴ�.");
		list->head = current->next;
		current->next->prev = NULL;
		free(current);
	}
	else if (current == list->tail)
	{
		printf("������ ��带 �����մϴ�.");
		list->tail = current->prev;
		current->prev->next = NULL;
		free(current);
	}
	else
	{
		printf("�����մϴ�.");
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