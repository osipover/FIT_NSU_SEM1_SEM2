#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
enum { N_MAX = 5000 };

void inputNumVertexes(int* numVertexes);
void inputNumEdges(int* numEdges, int numVertexes);
void buildMatrix(int** graph, int numVertexes);
void fillGraph(int** graph, int numEdges, int numVertexes);
void updateMinEdges(int** graph, long long int* minEdges, int* MST, bool* visited, int firstVert, int numVertexes);
int findNextVert(long long int* minEdges, bool* visited, int numVertexes);
void Prim(int** graph, bool* visited, long long int* minEdges, int* MST, int numVertexes);
void fillArrays(bool* visited, long long int* minEdges, int* MST, int numVertexes);
bool isTreeConnected(int* MST, int numVertexes);
void freeArrays(bool* visited, long long int* minEdges, int* MST);
void printMST(int* MST, int numVertexes);
void buildMST(int** graph, int numVertexes);
void freeGraph(int** graph, int numVertexes);

int main() {
    int numVertexes;
    inputNumVertexes(&numVertexes);
    int numEdges;
    inputNumEdges(&numEdges, numVertexes);
    int** graph = malloc(numVertexes * sizeof(int*));
    assert(graph);
    fillGraph(graph, numEdges, numVertexes);
    buildMST(graph, numVertexes);
    freeGraph(graph, numVertexes);
    return 0;
}

void inputNumVertexes(int* numVertexes) {
    if (scanf("%d", numVertexes) != 1)
        exit(0);
    if (*numVertexes == 0) {
        printf("no spanning tree");
        exit(0);
    }
    if (((*numVertexes) < 0) || ((*numVertexes) > N_MAX)) {
        printf("bad number of vertices");
        exit(0);
    }
}

void inputNumEdges(int* numEdges, int numVertexes) {
    if (scanf("%d", numEdges) != 1)
        exit(0);
    if ((*numEdges < 0) || ((numVertexes * (numVertexes + 1) / 2) < *numEdges)) {
        printf("bad number of edges");
        exit(0);
    }
}

void buildMatrix(int** graph, int numVertexes) {
    for (int i = 0; i < numVertexes; ++i) {
        graph[i] = (int*)calloc(numVertexes, sizeof(int));
        assert(graph[i]);
    }

}

void fillGraph(int** graph, int numEdges, int numVertexes) {
    buildMatrix(graph, numVertexes);
    for (int i = 0; i < numEdges; ++i) {
        int firstVert, secondVert, weightEdge;
        if (scanf("%d %d %d", &firstVert, &secondVert, &weightEdge) != 3) {
            printf("bad number of lines");
            exit(0);
        }
        if ((firstVert < 1) || (numVertexes < firstVert) || (secondVert < 1) || (numVertexes < secondVert)) {
            printf("bad vertex");
            exit(0);
        }
        if ((weightEdge < 0) || (INT_MAX < weightEdge)) {
            printf("bad length");
            exit(0);
        }
        graph[firstVert - 1][secondVert - 1] = weightEdge;
        graph[secondVert - 1][firstVert - 1] = weightEdge;
    }
}


void updateMinEdges(int** graph, long long int* minEdges, int* MST, bool* visited, int firstVert, int numVertexes) {
    for (int secondVert = 0; secondVert < numVertexes; ++secondVert) {
        if ((graph[firstVert][secondVert] < minEdges[secondVert]) && (graph[firstVert][secondVert] != 0) && (!visited[secondVert])) {
            minEdges[secondVert] = graph[firstVert][secondVert];
            MST[secondVert] = firstVert;
        }
    }
}

int findNextVert(long long int* minEdges, bool* visited, int numVertexes) {
    int nextVert = 0;
    for (int i = 0; i < numVertexes; ++i) {
        if ((!visited[i]) && (minEdges[i] < minEdges[nextVert])) 
            nextVert = i;
    }
    visited[nextVert] = true;
    return nextVert;
}

void Prim(int** graph, bool* visited, long long int* minEdges, int* MST, int numVertexes) {
    for (int i = 0; i < numVertexes - 1; ++i) {
        int nextVert = findNextVert(minEdges, visited, numVertexes);
        updateMinEdges(graph, minEdges, MST, visited, nextVert, numVertexes);
    }
}

void fillArrays(bool* visited, long long int* minEdges, int* MST, int numVertexes) {
    for (int i = 0; i < numVertexes; ++i) {
        visited[i] = false;
        minEdges[i] = LLONG_MAX;
        MST[i] = -1;
    }
}

bool isTreeConnected(int* MST, int numVertexes) {
    for (int i = 1; i < numVertexes; ++i) {
        if (MST[i] == -1)
            return false;
    }
    return true;
}

void freeArrays(bool* visited, long long int* minEdges, int* MST) {
    free(visited);
    free(minEdges);
    free(MST);
}

void printMST(int* MST, int numVertexes) {
    for (int i = 1; i < numVertexes; ++i)
        printf("%d %d\n", i + 1, MST[i] + 1);
}

void buildMST(int** graph, int numVertexes) {
    bool* visited = malloc(sizeof(bool) * numVertexes);
    long long int* minEdges = malloc(sizeof(long long int) * numVertexes);
    int* MST = malloc(sizeof(int) * numVertexes);
    fillArrays(visited, minEdges, MST, numVertexes);
    Prim(graph, visited, minEdges, MST, numVertexes);
    if (!isTreeConnected(MST, numVertexes)) {
        printf("no spanning tree");
        freeArrays(visited, minEdges, MST);
        return;
    }
    printMST(MST, numVertexes);
    freeArrays(visited, minEdges, MST);
}

void freeGraph(int** graph, int numVertexes) {
    for (int i = 0; i < numVertexes; ++i)
        free(graph[i]);
    free(graph);
}
