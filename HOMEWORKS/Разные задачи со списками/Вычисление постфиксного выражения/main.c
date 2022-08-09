#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

void PushList(TValue value, TList** list) {
	TList* new = malloc(sizeof(TList));
	assert(new != NULL);
	new->next = NULL;
	new->value = value;

	if (*list == NULL) {
		*list = new;
		return;
	}

	TList* tmp = *list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	
	tmp->next = new;
}

bool IsDigit(char symbol) {
	if (('0' <= symbol) && (symbol <= '9'))
		return true;
	else
		return false;
}

bool IsOperator(int symbol) {
	if ((symbol == (int)'+') || (symbol == (int)'-') || (symbol == (int)'*') || (symbol == (int)'/'))
		return true;
	else
		return false;
}

TList* ConvertStringToList(char* string, int length) {
	TList* postfix = NULL;

	int digit = 0;
	for (int i = 0; i <= length; ++i) {
		if (IsDigit(string[i])) {
			while (IsDigit(string[i])) {
				digit = digit * 10 + string[i] - '0';
				++i;
			}
			PushList(digit, &postfix);
			digit = 0;
		}
		if (IsOperator((int)string[i]))
			PushList((int)string[i], &postfix);
	}

	return postfix;
}

bool IsListEmpty(TList* list) {
	if (list == NULL)
		return true;
	else
		return false;
}

void PrintList(TList* list) {
	while (!IsListEmpty(list)) {
		printf("%d ", list->value);
		list = list->next;
	}
	printf("\n");
}

bool IsNumber(int symbol) {
	if (!IsOperator(symbol))
		return true;
	else
		return false;
}

void PushStack(TValue value, TList** stack) {
	TList* node = malloc(sizeof(TList));
	node->value = value;
	node->next = *stack;
	*stack = node;
}

int PopStack(TList** stack) {
	TValue value = (*stack)->value;
	TList* tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	return value;
}

int GetResultOfOperation(int a, int b, char operator) {
	switch (operator) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			assert(b != 0);
			return a / b;
	}
}

int CalcPostfix(TList* postfix) {
	TList* stack = NULL;

	while (!IsListEmpty(postfix)) {
		if (IsNumber(postfix->value))
			PushStack(postfix->value, &stack);
		else {
			int b = PopStack(&stack);
			int a = PopStack(&stack);
			int result = GetResultOfOperation(a, b, (char)postfix->value);
			PushStack(result, &stack);
		}
		postfix = postfix->next;
	}

	int answer = PopStack(&stack);
	assert(IsListEmpty(stack));
	return answer;
}
void FreeList(TList** node) {
	while (!IsListEmpty(*node)) {
		TList* tmp = *node;
		*node = (*node)->next;
		free(tmp);
	}
}

int main() {
	char* string = "1 2 3 * +";
	int length = strlen(string);

	TList* postfix = ConvertStringToList(string, length);

	int answer = CalcPostfix(postfix);
	printf("%d", answer);

	FreeList(&postfix);

	return SUCCESS;
}
