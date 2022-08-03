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

void PushBack(TList* node, TList** list) {
	TList* tmp = *list;
	while (!IsListEmpty(tmp->next))
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}

void FreeList(TList** list) {
	while (!IsListEmpty(*list)) {
		TList* tmp = *list;
		(*list) = tmp->next;
		free(tmp);
	}
}

void Rotate(TList** list) {
	if (IsListEmpty(*list) || (IsListEmpty((*list)->next)))
		return;
	TList* head = *list;
	*list = (*list)->next;
	PushBack(head, list);
}

int main() {
	int array[] = { 1, 2, 3, 4, 5 };
	int size = sizeof(array) / sizeof(int);
	TList* list = ConvertListFromArray(array, size);
	PrintList(list);
	Rotate(&list);
	PrintList(list);
	FreeList(&list);

	return SUCCESS;
}
