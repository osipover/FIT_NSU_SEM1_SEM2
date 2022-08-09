#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

enum WORK_RESULT {
	SUCCESS = 0,
	FAILURE = 1
};

typedef int TValue;

typedef struct TStack {
	TValue value;
	struct TStack* next;
}TStack;

typedef struct TQueue {
	TStack* forEnq;
	TStack* forDeq;
}TQueue;

TQueue* CreateQueue() {
	TQueue* queue = malloc(sizeof(TQueue));
	assert(queue != NULL);
	queue->forEnq = NULL;
	queue->forDeq = NULL;
	return queue;
}

bool IsStackEmpty(TStack* stack) {
	if (stack == NULL)
		return true;
	else
		return false;
}

void Enqueue(TValue value, TQueue* queue) {
	TStack* node = malloc(sizeof(TStack));
	assert(node != NULL);
	node->value = value;
	node->next = queue->forEnq;
	queue->forEnq = node;
}

void Push(TValue value, TStack** stack) {
	TStack* node = malloc(sizeof(TStack));
	node->value = value;
	node->next = *stack;
	*stack = node;
}

TValue Pop(TStack** stack) {
	TValue value = (*stack)->value;
	TStack* tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	return value;
}

void PutForenqToFordeq(TQueue* queue) {
	TValue value;
	while (!IsStackEmpty(queue->forEnq)) {
		value = Pop(&(queue->forEnq));
		Push(value, &(queue->forDeq));
	}
}

TValue Dequeue(TQueue* queue) {
	if (IsStackEmpty(queue->forDeq))
		PutForenqToFordeq(queue);
	TValue value = Pop(&(queue->forDeq));
	return value;
}

void ConvertArrayToQueue(int* array, int size, TQueue* queue) {
	for (int i = 0; i < size; ++i)
		Enqueue(array[i], queue);
}

void PrintForDeq(TStack* list) {
	while (!IsStackEmpty(list)) {
		printf("%d ", list->value);
		list = list->next;
	}
}

void PrintForEnq(TStack* forEnq) {
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

void FreeStack(TStack** node) {
	while (!IsStackEmpty(*node)) {
		TStack* tmp = *node;
		*node = (*node)->next;
		free(tmp);
	}
}

void FreeQueue(TQueue* queue) {
	FreeStack(&(queue->forEnq));
	FreeStack(&(queue->forDeq));
}

void BuildTest(TQueue* queue) {
	PrintQueue(queue);

	TValue x = Dequeue(queue);
	Enqueue(6, queue);
	Enqueue(7, queue);

	PrintQueue(queue);

	x = Dequeue(queue);

	PrintQueue(queue);
}

int main() {
	int array[] = {1, 2, 3, 4, 5};
	int sizeOfArray = sizeof(array) / sizeof(int);

	TQueue* queue = CreateQueue();
	ConvertArrayToQueue(array, sizeOfArray, queue);

	BuildTest(queue);

	FreeQueue(queue);
	
	return SUCCESS;
}
