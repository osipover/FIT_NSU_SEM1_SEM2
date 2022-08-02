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

TList* getNth(TList* list, int n) {
	if (!IsListEmpty(list)) {
		int counter = 0;
		while ((counter < n) && (!IsListEmpty(list->next))) {
			list = list->next;
			++counter;
		}
	}
	return list;
}

void DeleteNth(TList** list, int n) {
	if (!IsListEmpty(*list)) {
		TList* delNode = NULL;

		if (n == 0) {
			delNode = *list;
			*list = (*list)->next;
			free(delNode);
			return;
		}

		TList* prev = getNth(*list, n-1);
		delNode = prev->next;
		prev->next = delNode->next;
		free(delNode);
	}
}

int main() {
	int array[] = { 1, 2, 3 };
	int size = sizeof(array) / sizeof(int);

	TList* list = ConvertListFromArray(array, size);

	PrintList(list);

	int n;
	assert((scanf("%d", &n) == 1) && (n >= 0) && (n < size));

	DeleteNth(&list, n);

	PrintList(list);
}
