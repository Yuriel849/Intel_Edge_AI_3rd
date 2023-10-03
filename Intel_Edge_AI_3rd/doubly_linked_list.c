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
	// ����� ��ŷ �ۿ��� �ֱٿ� ��ü�� ���¹�ȣ ���
	int i, selection, acct_num, order = 0; // order == 0�̸� �ֽ� ��, order == 1�̸� ������ ��
	const int MAX_NUMBER = 54321; // ���¹�ȣ �ְ�
	const int MIN_NUMBER = 12345; // ���¹�ȣ �ּҰ�

	DLL* acct_list = (DLL*)malloc(sizeof(DLL));
	
	init(acct_list);
	srand(time(NULL));

	for (i = 0; i < 20; i++)
	{
		insert(acct_list, i, (rand() % (MAX_NUMBER + 1 - MIN_NUMBER)) + MIN_NUMBER); // �������� ���¹�ȣ 20�� ����
	}

	while (1) // ����ڰ� ������ ������ ���� �ݺ�
	{
		selection = 0; // ����ڰ� ������ �۾� �ʱ�ȭ
		acct_num = 0; // ����ڰ� �Է��� ���¹�ȣ �ʱ�ȭ

		printf("\n==== �ֱٿ� ��ü�� ���¹�ȣ ����Դϴ�. ====\n");
		if (order == 0)
		{
			printf("============== �ֽ� ���Դϴ�. ==============\n");
			show_head_to_tail(acct_list);
		}
		else
		{
			printf("============== ������ ���Դϴ�. ==============\n");
			show_tail_to_head(acct_list);
		}
		printf("============================================\n");
		printf("======= ������ �۾��� �������ּ���. ========\n");
		printf("======== 1. �ֽ� ������ �����մϴ�. ========\n");
		printf("======= 2. ������ ������ �����մϴ�. =======\n");
		printf("===== 3. ���ο� ���¹�ȣ�� �߰��մϴ�. =====\n");
		printf("===== 4. ��ϵ� ���¹�ȣ�� �����մϴ�. =====\n");
		printf("===== 5. ����� ���¹�ȣ�� �˻��մϴ�. =====\n");
		printf("============== 6. �����մϴ�. ==============\n");
		scanf("%d", &selection);

		switch (selection)
		{
		case 1: show_head_to_tail(acct_list); order = 0; break;
		case 2: show_tail_to_head(acct_list); order = 1; break;
		case 3:
			printf("===== ���ο� ���¹�ȣ�� �Է����ּ���. ======\n");
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
			printf("===== ������ ���¹�ȣ�� �Է����ּ���. ======\n");
			scanf("%d", &acct_num);
			delete(acct_list, acct_num);
			break;
		case 5:
			printf("===== �˻��� ���¹�ȣ�� �Է����ּ���. ======\n");
			scanf("%d", &acct_num);
			NODE* node = find(acct_list, acct_num);
			if (node == NULL)
			{
				printf("> �������� �ʴ� ���¹�ȣ�Դϴ�.=============\n\n");
			}
			else
			{
				printf("> ã�ҽ��ϴ� : %5d\n ==================\n\n", node->id);
			}
			break;
		case 6:
			exit(0);
		default:
			printf("�ٽ� �������ּ���\n\n");
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
		printf("�� ����Ʈ�Դϴ�.\n");
	}
	else
	{
		printf("�� ����Ʈ�� �ƴմϴ�.\n");
	}
}

// ������ ID "after_here"�� ���� ��� ������ �߰��ϰų�, ã�� ���� ��� ���� �������� tail ������ �߰��Ѵ�.
void insert(DLL* list, int after_here, int new_id)
{
	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->id = new_id;
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