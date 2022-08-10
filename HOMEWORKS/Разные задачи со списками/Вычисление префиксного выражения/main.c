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

void PushList(TValue value, TList** list) {
	TList* new = CreateItem(value, NULL);

	if (*list == NULL)
		*list = new;
	else {
		TList* tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
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
bool IsNumber(int symbol) {
	if (!IsOperator(symbol))
		return true;
	else
		return false;
}

int PopList(TList** list) {
	TValue value = (*list)->value;
	TList* tmp = *list;
	*list = (*list)->next;
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

int CalcPrefix(TList** prefix) {
	int item = PopList(prefix);
	if (IsNumber(item))
		return item;
	else {
		int first = CalcPrefix(prefix);
		int second = CalcPrefix(prefix);
		return GetResultOfOperation(first, second, (char)item);
	}
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

int main() {
	char* string = "+ 1 * 2 3";
	int length = strlen(string);
	
	TList* prefix = ConvertStringToList(string, length);

	int answer = CalcPrefix(&prefix);
	printf("%d", answer);

	assert(prefix == NULL);

	return SUCCESS;
}
