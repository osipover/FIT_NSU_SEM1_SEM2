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

typedef struct TQueue {
	TList* forEnq;
	TList* forDeq;
}TQueue;

bool IsListEmpty(TList* stack) {
	if (stack == NULL)
		return true;
	else
		return false;
}

TQueue* CreateQueue() {
	TQueue* queue = malloc(sizeof(TQueue));
	assert(queue != NULL);
	queue->forEnq = NULL;
	queue->forDeq = NULL;
	return queue;
}

TList* CreateItem(TValue value, TList* list) {
	TList* newNode = malloc(sizeof(TList));
	assert(newNode != NULL);
	newNode->value = value;
	newNode->next = list;
	return newNode;
}

void PushStack(TValue value, TList** stack) {
	TList* node = CreateItem(value, *stack);
	*stack = node;
}

TValue PopStack(TList** stack) {
	TValue value = (*stack)->value;
	TList* tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	return value;
}

void MoveForenqToFordeq(TQueue* queue) {
	TValue value;
	while (!IsListEmpty(queue->forEnq)) {
		value = PopStack(&(queue->forEnq));
		PushStack(value, &(queue->forDeq));
	}
}

void Enqueue(TValue value, TQueue* queue) {
	TList* node = CreateItem(value, queue->forEnq);
	queue->forEnq = node;
}

TValue Dequeue(TQueue* queue) {
	if (IsListEmpty(queue->forDeq))
		MoveForenqToFordeq(queue);
	TValue value = PopStack(&(queue->forDeq));
	return value;
}

void PrintForDeq(TList* list) {
	while (!IsListEmpty(list)) {
		printf("%d ", list->value);
		list = list->next;
	}
}

void PrintForEnq(TList* forEnq) {
	if (forEnq == NULL)
		return;
	PrintForEnq(forEnq->next);
	printf("%d ", forEnq->value);
}

void PrintQueue(TQueue* queue) {
	PrintForDeq(queue->forDeq);
	PrintForEnq(queue->forEnq);

	printf("\n");
}

void FreeStack(TList** node) {
	while (!IsListEmpty(*node)) {
		TList* tmp = *node;
		*node = (*node)->next;
		free(tmp);
	}
}

void FreeQueue(TQueue* queue) {
	FreeStack(&(queue->forEnq));
	FreeStack(&(queue->forDeq));
}

void ConvertArrayToQueue(int* array, int size, TQueue* queue) {
	for (int i = 0; i < size; ++i)
		Enqueue(array[i], queue);
}

void BuildTest(TQueue* queue) {
	printf("Queue: ");
	PrintQueue(queue);
	
	printf("Dequeue: %d\nQueue: ", Dequeue(queue));
	PrintQueue(queue);

	printf("Enqueue: 6\nEnqueue: 7\nQueue: ");
	Enqueue(6, queue);
	Enqueue(7, queue);
	PrintQueue(queue);

	printf("Dequeue: %d\nQueue: ", Dequeue(queue));
	PrintQueue(queue);
}

int main() {
	int array[] = { 1, 2, 3, 4, 5 };
	int sizeOfArray = sizeof(array) / sizeof(int);

	TQueue* queue = CreateQueue();
	ConvertArrayToQueue(array, sizeOfArray, queue);

	BuildTest(queue);

	FreeQueue(queue);

	return SUCCESS;
}
