#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
enum {N_MAX = 2000};
int index = 0;

bool inputQuantity(int* N, int* M); //ввод количества вершин и ребер
bool CheckQuantity(int N, int M); //проверка количества вершин и ребер
bool inputVertex(int N, int M, char* matrix); //ввод начала и конца ребра
bool CheckVertices(int i, int j, int N); //проверка значений вершин
void DFS(char* visited, char* matrix, int* tops, int i, int N); //Depth-First Search - обход графа в глубину
void topsort(char* matrix, int N); //топологическая сортировка графа

int main(void) {
	int N, M;
	if (inputQuantity(&N, &M) == false)
		return 0;
	if (CheckQuantity(N, M) == false) 
		return 0;
	char* matrix = (char *)calloc(N*N, sizeof(char));
	assert(matrix);
	if (inputVertex(N, M, matrix) == false)
		return 0;
	topsort(matrix, N);
	free(matrix);
	return 0;
}

bool inputQuantity(int* N, int* M) {
	if (scanf("%d %d", N, M) != 2) {
		printf("bad number of lines");
		return false;
	}
	return true;
}

bool CheckQuantity(int N, int M) {
	if ((N < 0) || (N > N_MAX)) {
		printf("bad number of vertices");
		return false;
	}
	if ((M < 0) || ((N * (N + 1) / 2) < M)) {
		printf("bad number of edges");
		return false;
	}
	return true;
}

bool inputVertex(int N, int M, char* matrix) {
	for (int count = 0; count < M; ++count) {
		int i, j;
		if (scanf("%d %d", &i, &j) != 2) {
			printf("bad number of lines");
			free(matrix);
			return false;
		}

		if (CheckVertices(i, j, N) == 0) {
			printf("bad vertex");
			free(matrix);
			return false;
		}
		matrix[(i - 1) * N + (j - 1)] = 1;
	}
	return true;
}

bool CheckVertices(int i, int j, int N) {
	if ((i < 1) || (N < i))
		return false;
	if ((j < 1) || (N < j))
		return false;
	return true;
}

void DFS(char* visited, char* matrix, int* tops, int i, int N) {
	if (visited[i - 1] == 2)
		return;
	if (visited[i - 1] == 1) {
		printf("impossible to sort");
		exit(0);
	}
	visited[i - 1] = 1;
	for (int j = 1; j <= N; j++) {
		if ((matrix[(i - 1) * N + (j - 1)] == 1) && (visited[j - 1] != 2))
			DFS(visited, matrix, tops, j, N);
	}
	visited[i - 1] = 2;
	tops[index] = i;
	++index;
	return;
}

void topsort(char* matrix, int N) {
	char* visited = (char*)calloc(N, sizeof(char));
	assert(visited);
	int* tops = (int*)calloc(N, sizeof(int));
	assert(tops);
	for (int i = 1; i <= N; ++i)
		DFS(visited, matrix, tops, i, N);
	for (int i = N; i > 0; --i)
		printf("%d ", tops[i - 1]);
	free(visited);
	free(tops);
}
