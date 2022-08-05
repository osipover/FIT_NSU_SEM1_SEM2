#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

enum WORK_RESULT {
	SUCCESS = 0,
	FAILURE = 1
};

typedef int TValue;

typedef struct TList {
	TValue value;
	struct TList* next;
}TList;

bool IsListEmpty(TList* list) {
	if (list == NULL)
		return true;
	else
		return false;
}

void Push(TValue value, TList** list) {
	TList* new = malloc(sizeof(TList));
	assert(new != NULL);
	new->value = value;
	new->next = *list;
	*list = new;
}

void PrintList(TList* list) {
	while (!IsListEmpty(list)) {
		printf("%d ", list->value);
		list = list->next;
	}
	printf("\n");
}

TList* ConvertListFromArray(int* array, int size) {
	TList* list = NULL;
	for (int i = size - 1; i >= 0; --i)
		Push(array[i], &list);
	return list;
}

void FreeList(TList* list) {
	while (!IsListEmpty(list)) {
		TList* tmp = list;
		(list) = tmp->next;
		free(tmp);
	}
}

void PushBack(TList** list, TList** node) {
	if (*list == NULL) {
		*list = *node;
		*node = (*node)->next;
		(*list)->next = NULL;
		return;
	}

	TList* tmp = *list;

	while (!IsListEmpty(tmp->next))
		tmp = tmp->next;

	tmp->next = *node;
	*node = (*node)->next;
	tmp->next->next = NULL;
};

void SplitByIncrease(TList** list1, TList** list2, TList* list) {
	if (list == NULL)
		return;

	TValue prev = list->value;
	int count = 0;
	while (!IsListEmpty(list)) {
		if (list->value < prev)
			++count;
		prev = list->value;
		switch (count % 2) {
		case 0:
			PushBack(list1, &list);
			break;
		case 1:
			PushBack(list2, &list);
			break;
		}
	}
}

int main() {
	int array[] = { 1, 2, 3, 4, 2, 5, 7, 9, -1, -2, 0};
	int size = sizeof(array) / sizeof(int);

	TList* list = ConvertListFromArray(array, size);
	TList* list1 = NULL;
	TList* list2 = NULL;

	SplitByIncrease(&list1, &list2, list);

	PrintList(list1);
	PrintList(list2);


	FreeList(list1);
	FreeList(list2);

	return SUCCESS;
}
