#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

enum WORK_RESULT {
	SUCCESS = 0,
	FAILURE = 1
};

typedef char TValue;

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

int Pop(TList** list) {
	TValue value = (*list)->value;
	TList* tmp = *list;
	*list = (*list)->next;
	free(tmp);
	return value;
}

void PrintList(TList* list) {
	while (!IsListEmpty(list)) {
		printf("%c ", list->value);
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

void PushStack(TValue value, TList** stack) {
	TList* newNode = CreateItem(value, *stack);
	*stack = newNode;
}

bool IsBracketOpened(char bracket) {
	if ((bracket == '(') || (bracket == '{') || (bracket == '['))
		return true;
	else
		return false;
}

bool IsMatch(char bracket1, char bracket2) {
	if ((bracket1 == '(') && (bracket2 == ')'))
		return true;
	if ((bracket1 == '{') && (bracket2 == '}'))
		return true;
	if ((bracket1 == '[') && (bracket2 == ']'))
		return true;

	return false;

}

void CheckBrackets(TList** list) {
	TList* stack = NULL;
	char bracket;
	while (!IsListEmpty(*list)) {
		bracket = Pop(list);
		if (IsBracketOpened(bracket))
			PushStack(bracket, &stack);
		else {
			if (IsListEmpty(stack) || !IsMatch(Pop(&stack), bracket)) {
				printf("not OK");
				FreeList(list);
				return;
			}
		}
	}
	if (!IsListEmpty(stack)) {
		printf("not OK");
		FreeList(&stack);
	}
	else
		printf("OK");
}

TList* ConvertStringToList(char* string, int length) {
	TList* list = NULL;
	for (int i = 0; i < length; ++i)
		PushList(string[i], &list);
	return list;
}

int main() {
	char* string = "((){[]}}";
	int length = strlen(string);

	TList* list = ConvertStringToList(string, length);
	
	CheckBrackets(&list);
	
	return SUCCESS;
}
