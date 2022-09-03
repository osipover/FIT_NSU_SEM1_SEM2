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
} TList;

bool IsListEmpty(TList* list) {
	if (list == NULL)
		return true;
	else
		return false;
}

TList* CreateItem(TValue value, TList* list) {
	TList* new = malloc(sizeof(TList));
	assert(new != NULL);
	new->value = value;
	new->next = list;
	return new;
}

void PushStack(TValue value, TList** stack) {
	TList* newNode = CreateItem(value, *stack);
	*stack = newNode;
}

void PrintList(TList* list) {
	while (!IsListEmpty(list)) {
		printf("%d ", list->value);
		list = list->next;
	}
	printf("\n");
}

void FreeList(TList** node) {
	while (!IsListEmpty(*node)) {
		TList* tmp = *node;
		*node = (*node)->next;
		free(tmp);
	}
}

TValue GetStackValue(TList* stack) {
	return stack->value;
}

TList* GetNextNode(TList* stack) {
	return stack->next;
}

void Hanoi(int size, TList** stack1, TList** stack2, TList** buffer) {
	if (size == 0)
		return;
	else {
		Hanoi(size - 1, stack1, buffer, stack2);
		PushStack(GetStackValue(*stack1), stack2);
		*stack1 = GetNextNode(*stack1);
		Hanoi(size - 1, buffer, stack2, stack1);
	}
}

int GetSizeOfStack(TList* stack) {
	if (IsListEmpty(stack))
		return 0;
	else
		return 1 + GetSizeOfStack(stack->next);
}

TList* CopyStack(TList* stack1) {
	TList* stack2 = NULL;
	TList* buffer = NULL;
	Hanoi(GetSizeOfStack(stack1), &stack1, &stack2, &buffer);
	assert(buffer == NULL);
	return stack2;
}

TList* ConvertArrayToStack(int* array, int size) {
	TList* stack = NULL;
	for (int i = size - 1; i >= 0; --i)
		PushStack(array[i], &stack);
	return stack;
}

int main() {
	int array[] = { 1, 2, 3, 4, 5};

	TList* stack1 = ConvertArrayToStack(array, sizeof(array) / sizeof(int));
	TList* stack2 = CopyStack(stack1);
	
	PrintList(stack1);
	PrintList(stack2);

	FreeList(&stack1);
	FreeList(&stack2);

	return SUCCESS;
}
