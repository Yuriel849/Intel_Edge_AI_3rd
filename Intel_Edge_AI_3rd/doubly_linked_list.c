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
	printf("�˻��� ID�� �Է��ϼ��� : ");
	scanf("%d", &id_to_find);
	NODE* find_node = find(list, id_to_find);
	if (find_node == NULL)
	{
		printf("�������� �ʴ� ����Դϴ�.\n");
	}
	else
	{
		printf("ID : %d ��带 ã�ҽ��ϴ�.\n", id_to_find);
	}

	int id_to_delete;
	printf("������ ID�� �Է��ϼ��� : ");
	scanf("%d", &id_to_delete);
	delete(list, id_to_delete);
	show_head_to_tail(list);

	printf("�ٽ� �ѹ� Ȯ�����ּ���.\n");
	show_head_to_tail(list);
	show_tail_to_head(list);

	return 0;
}

void init(struct dll* list)
{
	(*list).head = NULL;
	list->tail = NULL;
}

// ������ ID "after_here"�� ���� ��� ������ �߰��ϰų�, ã�� ���� ��� ���� �������� tail ������ �߰��Ѵ�.
void insert(DLL* list, int after_here, int new_id, char data[])
{
	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->id = new_id;
	new->data[0] = data[0]; // �ڵ� ������ ���ǻ� ���ڿ��� ù ���ڸ� ����
	new->next = NULL;
	new->prev = NULL;

	NODE* current = (NODE*)malloc(sizeof(NODE));
	current = list->head;

	// ���� �� ����Ʈ�� ���ʷ� ��带 �߰��Ѵٸ�...
	if (current == NULL)
	{
		list->head = new;
		list->tail = new;
		return;
	}

	while (current != NULL)
	{
		// ���� ��尡 ������ ����� ���, �ٷ� �ڿ� ���ο� ��带 �߰��Ѵ�.
		if (current == list->tail)
		{
			new->prev = current;
			new->next = NULL;
			current->next = new;
			list->tail = new;
			return;
		}
		// ��ġ�ϴ� ID�� ���� ��带 ã���� ��� �� ���� ��ġ�� ���ο� ��带 �߰��Ѵ�.
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

	// ����Ʈ�� NULL ��ȯ
	return NULL;
}

void delete(DLL* list, int id)
{
	NODE* current = (NODE*)malloc(sizeof(NODE));
	current = find(list, id);
	
	if (current == NULL)
	{
		printf("ã���ô� ��尡 �������� �ʽ��ϴ�.\n");
	}
	else if (current == list->head)
	{
		printf("ù��° ��带 �����մϴ�.\n");
		list->head = current->next;
		current->next->prev = NULL;
		free(current);
	}
	else if (current == list->tail)
	{
		printf("������ ��带 �����մϴ�.\n");
		list->tail = current->prev;
		current->prev->next = NULL;
		free(current);
	}
	else
	{
		printf("�����մϴ�.\n");
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