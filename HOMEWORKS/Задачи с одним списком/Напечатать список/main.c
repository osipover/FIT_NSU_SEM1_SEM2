#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct TListOfDigits {
	int digit;
	struct TListOfDigits* next;
}TList;

void Push(int digit, TList** list) {
	TList* new = malloc(sizeof(TList));
	assert(new != NULL);
	new->digit = digit;
	new->next = *list;
	*list = new;
}

 bool IsListEmpty(TList* list) {
	 if (list == NULL)
		 return true;
	 else
		 return false;
 }

void CreateListOfDigits(unsigned int num, TList** list) {
	if (num == 0)
		Push(0, list);

	while (num > 0) {
		int digit = num % 10;
		Push(digit, list);
		num /= 10;
	}
}

 int SumList(TList* list) {
	int sum = 0;
	while (!IsListEmpty(list)) {
		sum += list->digit;
		list = list->next;
	}
	return sum;
}

void PrintList(TList* list) {
	printf("List of digits: ");
	while (!IsListEmpty(list)) {
		printf("%d ", list->digit);
		list = list->next;
	}
	printf("\n");
}

void FreeList(TList** list) {
	while (!IsListEmpty(*list)) {
		TList* tmp = *list;
		(*list) = tmp->next;
		free(tmp);
	}
}

int main() {
	unsigned int num;
	assert(scanf("%u", &num) == 1);
	TList* list = NULL;

	CreateListOfDigits(num, &list);

	PrintList(list);

	int sum = SumList(list);
	printf("Sum of list: %d", sum);

	FreeList(&list);
}
