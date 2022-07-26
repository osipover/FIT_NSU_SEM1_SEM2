#include <stdio.h>
#include <stdlib.h>

int** CreateMatrix(int rows, int columns) {
	int** matrix = malloc(sizeof(int*) * rows);
	for (int i = 0; i < rows; ++i)
		matrix[i] = malloc(sizeof(int) * columns);
	return matrix;
}

void FillMatrix(int** matrix, int rows, int columns) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (scanf("%d", &matrix[i][j]) != 1)
				return;
		}
	}
}

int SumElements(int** matrix, int rows, int columns) {
	int sum = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
			sum += matrix[i][j];
	}
	return sum;
}

int main() {
	int rows = 3, columns = 4;

	int** matrix = CreateMatrix(rows, columns);
	FillMatrix(matrix, rows, columns);

	int sum = SumElements(matrix, rows, columns);

	printf("%d", sum);
	
	return 0;
}
