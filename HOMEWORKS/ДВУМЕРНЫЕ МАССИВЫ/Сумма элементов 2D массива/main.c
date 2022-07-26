#include <stdio.h>
#include <stdlib.h>

int** CreateMatrix(int N, int M) {
	int** matrix = malloc(sizeof(int*) * N);
	for (int i = 0; i < N; ++i)
		matrix[i] = (int*)malloc(sizeof(int) * M);
	return matrix;
}

void FillMatrix(int** matrix, int N, int M) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (scanf("%d", &matrix[i][j]) != 1)
				return;
		}
	}
}

int SumElements(int** matrix, int N, int M) {
	int sum = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			sum += matrix[i][j];
	}
	return sum;
}

int main() {
	int N = 3, M = 4;

	int** matrix = CreateMatrix(N, M);
	FillMatrix(matrix, N, M);

	int sum = SumElements(matrix, N, M);

	printf("%d", sum);
	
	return 0;
}
