#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

enum WORK_RESULT {
	SUCCESS = 0,
	FAILURE  = 1
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

bool IsListSorted(TList* list) {
	if (IsListEmpty(list) || IsListEmpty(list->next))
		return true;

	if (!IsListEmpty(list) && !IsListEmpty(list->next)) {
		if (list->value > (list->next)->value)
			return false;
		IsListSorted(list->next);
	}
}

void Push(TValue value, TList** list) {
	TList* new = malloc(sizeof(TList));
	assert(new != NULL);
	new->value = value;
	new->next = *list;
	*list = new;
}

TList* ConvertListFromArray(int* array, int size) {
	TList* list = NULL;
	for (int i = size - 1; i >= 0; --i)
		Push(array[i], &list);
	return list;
}

void DeleteDublicate(TList** prev) {
	TList* dubl = (*prev)->next;
	(*prev)->next = dubl->next;
	free(dubl);
}

void RemoveDublicates(TList** list) {
	if (IsListEmpty(*list))
		return;
	
	TList* tmp = *list;

	while (!IsListEmpty(tmp) && !IsListEmpty(tmp->next)) {
		if (tmp->value == (tmp->next)->value)
			DeleteDublicate(&tmp);
		else
			tmp = tmp->next;
	}
}

void PrintList(TList* list) {
	while (!IsListEmpty(list)) {
		printf("%d ", list->value);
		list = list->next;
	}
	printf("\n");
}

int main() {
	int array[] = {1, 1, 2, 2, 3, 4, 5};
	int size = sizeof(array) / sizeof(int);

	TList* list = ConvertListFromArray(array, size);

	if (!IsListSorted(list))
		return FAILURE;

	PrintList(list);

	RemoveDublicates(&list);
	
	PrintList(list);

	return SUCCESS;
}
