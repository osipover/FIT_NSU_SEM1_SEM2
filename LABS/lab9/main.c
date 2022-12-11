#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#define N_MAX 5000
int checkOverflow = 0;

void InputNumVertex(int* numVertexes);
void InputStartFinish(int* startVertex, int* finishVertex, int numVertexes);
void InputNumEdges(int* numEdges, int numVertexes);
bool InputVertexes(int* matrix, int numEdges, int numVertexes);
void FindShortestPaths(long long int* shortestPaths, int startVertex, int* matrix, char* visited, int* optimalRoute, int numVertexes);
void Deikstra(long long int* shortestPaths, int* matrix, char* visited, int* optimalRoute, int startVertex, int numVertexes);
void PrintShortestPaths(long long int* shortestPaths, int numVertexes);
void FindOptimalRoute(long long int* shortestPaths, int finishVertex, int* optimalRoute, int startVertex);
void PrintOptimalRoute(int* optimalRoute, int curentVertex, int startVertex);
void FreeArrays(int* matrix, long long int* shortestPaths, char* visited, int* optimalRoute);

int main() {
    int numVertexes;
    InputNumVertex(&numVertexes);
    int startVertex, finishVertex;
    InputStartFinish(&startVertex, &finishVertex, numVertexes);
    int numEdges;
    InputNumEdges(&numEdges, numVertexes);
    int* matrix = (int*)calloc(numVertexes * numVertexes, sizeof(int));
    assert(matrix);
    if (InputVertexes(matrix, numEdges, numVertexes) == false) {
        free(matrix);
        return 0;
    }
    long long int* shortestPaths = (long long int*)malloc(sizeof(long long int) * numVertexes);
    assert(shortestPaths);
    char* visited = (char*)calloc(numVertexes, sizeof(char));
    assert(visited);
    int* optimalRoute = (int*)malloc(sizeof(int) * numVertexes);
    assert(optimalRoute);
    FindShortestPaths(shortestPaths, startVertex, matrix, visited, optimalRoute, numVertexes);
    FindOptimalRoute(shortestPaths, finishVertex, optimalRoute, startVertex);
    FreeArrays(matrix, shortestPaths, visited, optimalRoute);
    return 0;
}

void InputNumVertex(int* numVertexes) {
    if (scanf("%d ", numVertexes) != 1)
        exit(0);
    if (((*numVertexes) < 0) || ((*numVertexes) > N_MAX)) {
        printf("bad number of vertices");
        exit(0);
    }
}

void InputStartFinish(int* startVertex, int* finishVertex, int numVertexes) {
    if (scanf("%d %d", startVertex, finishVertex) != 2)
        exit(0);
    if ((*startVertex < 1) || (numVertexes < *startVertex) || (*finishVertex < 1) || (numVertexes < *finishVertex)) {
        printf("bad vertex");
        exit(0);
    }
}

void InputNumEdges(int* numEdges, int numVertexes) {
    if (scanf("%d", numEdges) != 1)
        exit(0);
    if ((*numEdges < 0) || ((numVertexes * (numVertexes + 1) / 2) < *numEdges)) {
        printf("bad number of edges");
        exit(0);
    }
}

bool InputVertexes(int* matrix, int numEdges, int numVertexes) {
    for (int count = 0; count < numEdges; ++count) {
        int startVertex, endVertex, lengthVertex;
        if (scanf("%d %d %d", &startVertex, &endVertex, &lengthVertex) != 3)
            return false;
        if ((startVertex < 1) || (numVertexes < startVertex) || (endVertex < 1) || (numVertexes < endVertex)) {
            printf("bad vertex");
            return false;
        }
        if ((lengthVertex < 0) || (INT_MAX < lengthVertex)) {
            printf("bad length");
            return false;
        }
        matrix[(startVertex - 1) * numVertexes + (endVertex - 1)] = lengthVertex;
        matrix[(endVertex - 1) * numVertexes + (startVertex - 1)] = lengthVertex;
    }
    return true;
}

void FindShortestPaths(long long int* shortestPaths, int startVertex, int* matrix, char* visited, int* optimalRoute, int numVertexes) {
    for (int i = 0; i < numVertexes; ++i)
        shortestPaths[i] = LLONG_MAX;
    shortestPaths[startVertex - 1] = 0;
    Deikstra(shortestPaths, matrix, visited, optimalRoute, startVertex - 1, numVertexes);
    PrintShortestPaths(shortestPaths, numVertexes);
}

void Deikstra(long long int* shortestPaths, int* matrix, char* visited, int* optimalRoute, int startVertex, int numVertexes) {
    int curentIndex = startVertex * numVertexes;
    int indexMinMarker = numVertexes - 1;
    long long int minMarker = LLONG_MAX;
    for (int i = 0; i < numVertexes; ++i) {
        if ((shortestPaths[i] <= minMarker) && (visited[i] == 0) && (i != startVertex)) {
            minMarker = shortestPaths[i];
            indexMinMarker = i;
        }
    }
    for (int nextVertex = curentIndex; nextVertex < curentIndex + numVertexes; ++nextVertex) {
        if (nextVertex != curentIndex * numVertexes + curentIndex) {
            if ((matrix[nextVertex] > 0) && (visited[nextVertex - curentIndex] == 0)) {
                long long int marker = shortestPaths[startVertex] + matrix[nextVertex];
                if (marker > INT_MAX)
                    ++checkOverflow;
                int numNextVertex = nextVertex - curentIndex;
                if (marker < shortestPaths[numNextVertex]) {
                    shortestPaths[numNextVertex] = marker;
                    optimalRoute[numNextVertex] = startVertex;
                    if (marker < minMarker) {
                        minMarker = marker;
                        indexMinMarker = numNextVertex;
                    }
                }
            }
        }
    }
    visited[startVertex] = 1;
    if (visited[indexMinMarker] == 0)
        Deikstra(shortestPaths, matrix, visited, optimalRoute, indexMinMarker, numVertexes);
    return;
}

void PrintShortestPaths(long long int* shortestPaths, int numVertexes) {
    for (int i = 0; i < numVertexes; ++i) {
        if (shortestPaths[i] == LLONG_MAX)
            printf("oo ");
        else if (shortestPaths[i] > INT_MAX)
            printf("INT_MAX+ ");
        else
            printf("%lld ", shortestPaths[i]);
    }
    printf("\n");
}

void PrintOptimalRoute(int* optimalRoute, int curentVertex, int startVertex) {
    if (curentVertex == startVertex) {
        printf("%d", curentVertex + 1);
        return;
    }
    else {
        printf("%d ", curentVertex + 1);
        PrintOptimalRoute(optimalRoute, optimalRoute[curentVertex], startVertex);
    }
}

void FindOptimalRoute(long long int* shortestPaths, int finishVertex, int* optimalRoute, int startVertex) {
    if (shortestPaths[finishVertex - 1] == LLONG_MAX)
        printf("no path");
    else if ((shortestPaths[finishVertex - 1] > INT_MAX) && (checkOverflow >= 2))
        printf("overflow");
    else
        PrintOptimalRoute(optimalRoute, finishVertex - 1, startVertex - 1);
}

void FreeArrays(int* matrix, long long int* shortestPaths, char* visited, int* optimalRoute) {
    free(matrix);
    free(shortestPaths);
    free(visited);
    free(optimalRoute);
}
