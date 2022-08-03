#include <stdio.h>

void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void RemoveArray(int* array, int size) {
	for (int i = 0; i < size / 2; ++i)
		Swap(&array[i], &array[size - i - 1]);
}

void PrintArray(int* array, int size) {
	for (int i = 0; i < size; ++i)
		printf("%d ", array[i]);
}

int main() {
	int array[] = { 1, 2, 3, 4, 5 };
	int size = sizeof(array) / sizeof(int);
	RemoveArray(array, size);
	PrintArray(array, size);
	return 0;
}
