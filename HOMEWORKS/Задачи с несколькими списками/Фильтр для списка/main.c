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

void FreeList(TList** list) {
	while (!IsListEmpty(*list)) {
		TList* tmp = *list;
		(*list) = tmp->next;
		free(tmp);
	}
}

void DeleteNode(TList** curNode, TList** prev, TList** list) {
	TList* tmp = *curNode;
	if (*curNode == *prev) {
		*curNode = (*curNode)->next;
		*prev = *curNode;
		*list = *curNode;
		free(tmp);
		return;
	}
	(*curNode) = (*curNode)->next;
	(*prev)->next = (*curNode);
	free(tmp);

}

void DeleteRemains(TList** prev, TList** curNode, TList** list) {
	if (*prev == *curNode) {
		FreeList(list);
		return;
	}
	FreeList(curNode);
	(*prev)->next = NULL;
}

void FilterList(TList** list, TList* filter) {
	if (filter == NULL)
		return;

	TList* curNode = *list;
	TList* prev = *list;
	while (!IsListEmpty(filter) && !(IsListEmpty(curNode))) {
		if (filter->value == curNode->value) {
			prev = curNode;
			curNode = curNode->next;
		}
		else if (filter->value < curNode->value)
			filter = filter->next;
		else if (filter->value > curNode->value)
			DeleteNode(&curNode, &prev, list);
	}
	if (!IsListEmpty(curNode))
		DeleteRemains(&prev, &curNode, list);
}

int main() {
	int arrayList[] = { 1, 2, 2, 3, 4, 4, 4, 5};
	int sizeOfList = sizeof(arrayList) / sizeof(int);
	int arrayFilter[] = {1, 3, 3, 4};
	int sizeOfFilter = sizeof(arrayFilter) / sizeof(int);

	TList* list = ConvertListFromArray(arrayList, sizeOfList);
	TList* filter = ConvertListFromArray(arrayFilter, sizeOfFilter);

	FilterList(&list, filter);

	PrintList(list);

	FreeList(&list);
	FreeList(&filter);

	return SUCCESS;
}
