#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1002
typedef int Value;

typedef struct Stack {
	Value value;
	struct Stack* next;
} Stack;

void push(Stack** plist, Value value); //добавить новый элемент в стэк
Value pop(Stack** plist); //взять верхний элемент стека и удалить
Value GetTop(Stack** plist); //взять врехний элемент стека
void DelTop(Stack** plist); //удалить верхний элемент стека
int isEmpty(Stack* list); //проверка стека на наличие элементов 
int Priority(char op); //проверка приоритета операции
int SyntaxError(char* input); //проверка на наличие синтаксических ошибок
void BuildPolNotation(char* input, char* PolNotation, Stack* list); //построение обратной польской записи
void calculate(char* PolNotation, Stack* list); //вычисление из обратной польской записи

int main() {
	Stack* list = NULL;
	char input[SIZE] = { '\0' };
	if (fgets(input, SIZE, stdin) == 0) return 0;
	if (SyntaxError(input) == 1) {
		printf("syntax error");
		return 0;
	}
	else {
		char PolNotation[SIZE*2] = {'\0'};
		BuildPolNotation(input, PolNotation, list);
		calculate(PolNotation, list);
		return 0;
	}	
}

void push(Stack** plist, Value value) {
	Stack* p = malloc(sizeof(Stack));
	p->value = value;
	p->next = *plist;
	*plist = p;
}

Value pop(Stack** plist) {
	Stack* p = *plist;
	Value res = p->value;
	*plist = p->next;
	free(p);
	return res;
}

Value GetTop(Stack** plist) {
	Stack* p = *plist;
	return p->value;
}

void DelTop(Stack** plist) {
	Stack* p = *plist;
	*plist = p->next;
	free(p);

}

int isEmpty(Stack* list) {
	return list == NULL;
}

int Priority(char op) {
	switch (op) {
	case '(':
		return 1;
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	}
	return -1;
}

int SyntaxError(char* input) {
	int i = 0;
	int BracketsCheck = 0;
	if (input[0] == '\n')
		return 1;
	while (input[i] != '\n') {
		if (('0' <= input[i]) && (input[i] <= '9')) {
			++i;
			continue;
		}

		else if (input[i] == '(') {
			if ((input[i + 1] == ')') || (Priority(input[i + 1]) > 1))
				return 1;
			++BracketsCheck;
		}
		else if (input[i] == ')') {
			--BracketsCheck;
			if (BracketsCheck < 0)
				return 1;
		}
		else if (Priority(input[i]) > 1) {
			if ((Priority(input[i + 1]) > 1) || (input[i + 1] == '\n'))
				return 1;
		}
		else
			return 1;
		++i;
	}
	if (BracketsCheck != 0)
		return 1;
	return 0;
}

void BuildPolNotation(char* input, char* PolNotation, Stack* list) {
	int i = 0;
	int j = 0;
	while (input[i] != '\n') {
		if (('0' <= input[i]) && (input[i] <= '9')) {
			while (('0' <= input[i]) && (input[i] <= '9')) {
				PolNotation[j] = input[i];
				++i;
				++j;
			}
			PolNotation[j] = ' ';
			++j;

		}
		else if (input[i] == '(') {
			push(&list, (int)input[i]);
			++i;
		}
		else if (input[i] == ')') {
			if (!isEmpty(list)) {
				while ((char)GetTop(&list) != '(') {
					PolNotation[j] = (char)pop(&list);
					PolNotation[j + 1] = ' ';
					j += 2;
				}
			}
			DelTop(&list);
			++i;
		}
		else if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/')) {
			if (!isEmpty(list)) {
				char op = GetTop(&list);
				while (Priority(input[i]) <= Priority(op)) {
					PolNotation[j] = pop(&list);
					PolNotation[j + 1] = ' ';
					j += 2;
					if (!isEmpty(list)) {
						op = GetTop(&list);
					}
					else
						break;
				}

			}
			push(&list, input[i]);
			++i;
		}
	}
	while (!isEmpty(list)) {
		PolNotation[j] = pop(&list);
		PolNotation[j + 1] = ' ';
		j += 2;
	}
	if (PolNotation[j] == ' ') {
		PolNotation[j] = '\0';
	}
}

void calculate(char* PolNotation, Stack* list) {
	int i = 0;
	while (PolNotation[i] != '\0') {
		if (('0' <= PolNotation[i]) && (PolNotation[i] <= '9')) {
			int value = 0;
			while (PolNotation[i] != ' ') {
				value = value * 10 + (PolNotation[i] - '0');
				++i;
			}
			push(&list, value);
		}
		if (PolNotation[i] == ' ') {
			++i;
		}

		if (Priority(PolNotation[i]) > 1) {
			int op2 = pop(&list);
			int op1 = pop(&list);
			switch (PolNotation[i]) {
			case '+':
				push(&list, op1 + op2);
				break;
			case '-':
				push(&list, op1 - op2);
				break;
			case '*':
				push(&list, op1 * op2);
				break;
			case '/':
				if (op2 == 0) {
					while (list != NULL)
						DelTop(&list);
					printf("division by zero");
					return;
				}
				push(&list, op1 / op2);
				break;
			}
			++i;
		}
	}
	int result = pop(&list);
	printf("%d", result);
}
