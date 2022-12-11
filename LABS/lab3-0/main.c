#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int* b) {
	int box = *a;
	*a = *b;
	*b = box;
}

void heapify(int* arr, int index, int size) {
	int max = index;
	while (1) {
		int leftChild = index * 2 + 1;
		int rightChild = index * 2 + 2;
		if ( (leftChild < size) && (arr[leftChild] > arr[max]))
			max = leftChild;
		if ((rightChild < size) && (arr[rightChild] > arr[max]))
			max = rightChild;
		if (max == index)
			break;
		else {
			swap(&arr[index], &arr[max]);
			index = max;
		}
	}
}

void HeapSort(int* arr, int size) {
	for (int i = (size / 2) - 1; i >= 0; --i) {
		heapify(arr, i, size);
	}
	for (int i = size - 1; i >= 0; --i) {
		swap(&arr[0], &arr[i]);
		heapify(arr, 0, i);
	}
}
	
int main() {
	int size;
	if (scanf("%d", &size) != 1) return 0;
	int* arr = malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i) {
		if (scanf("%d", &arr[i]) != 1) return 0;
	}
	
	HeapSort(arr, size);

	for (int i = 0; i < size; ++i) {
		printf("%d ", arr[i]);
	}
	free(arr);
	return 0;
}
