#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 3
#define COLUMN 4

void FillRandValues(int matrix[ROW][COLUMN]) {
	srand(time(NULL));

	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COLUMN; ++j)
			matrix[i][j] = rand() % 100;
	}
}

void CopyMatrix(int matrix1[ROW][COLUMN], int matrix2[ROW][COLUMN]) {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COLUMN; ++j)
			matrix2[i][j] = matrix1[i][j];
	}
}

void PrintMatrix(int matrix[ROW][COLUMN]) {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COLUMN; ++j)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

int main() {
	int matrix1[ROW][COLUMN];
	int matrix2[ROW][COLUMN];

	FillRandValues(matrix1);

	printf("First matrix:\n");
	PrintMatrix(matrix1);

	CopyMatrix(matrix1, matrix2);

	printf("Second matrix:\n");
	PrintMatrix(matrix2);

	return 0;
}
