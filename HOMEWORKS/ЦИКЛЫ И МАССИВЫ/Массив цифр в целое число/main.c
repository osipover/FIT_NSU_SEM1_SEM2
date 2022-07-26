#include <stdio.h>

int GetNumFromArray(int* array, int size) {
	int num = 0;
	for (int i = size; i >= 0; --i) {
		num = num * 10 + array[i];
	}
	return num;
}

int main() {
	int array[] = { 3, 2, 1 };
	int size = sizeof(array) / sizeof(int) - 1;
	printf("%d", GetNumFromArray(array, size));
}
