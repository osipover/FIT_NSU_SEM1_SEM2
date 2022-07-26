#include <stdio.h>
#include <math.h>

void GetArrayFromNum(int num, int* array, int size) {
	for (int i = 0; i < size; ++i) {
		if (num > 0) {
			array[i] = num % 10;
			num /= 10;
		}
		else
			array[i] = 0;
	}
}

void PrintArray(int* array, int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d ", array[i]);
	}
}

int main() {
	int num;
	if (scanf("%d", &num) != 1)
		return 1;
	int array[10];
	int size = sizeof(array) / sizeof(int);
	GetArrayFromNum(num, array, size);
	PrintArray(array, size);
	return 0;
}
