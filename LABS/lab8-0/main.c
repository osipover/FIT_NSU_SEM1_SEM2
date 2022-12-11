#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
enum { N_MAX = 5000 };

typedef struct Edge {
    int firstVert;
    int secondVert;
    int weightEdge;
    bool isEdgeInTree;
}Edge;

void inputNumVertexes(int* numVertexes);
void inputNumEdges(int* numEdges, int numVertexes);
void fillEdge(Edge* graph, int firstVert, int secondVert, int weightEdge, int index);
void fillGraph(Edge* graph, int numEdges, int numVertexes);
void swap(Edge* pLeft, Edge* pRight);
void QuickSort(Edge* graph, int first, int last);
void printGraph(Edge* graph, int numEdges);
void fillParentAndRank(int* parent, int* rank, int numVertexes);
int find(int* parent, int vert);
void unite(int* parent, int* rank, int parentFirst, int parentSecond);
void Kraskal(int* parent, int* rank, Edge* graph, int numEdges);
bool isGraphConnected(int* parent, int numVertexes);
void freeMemory(int* parent, int* rank);
void buildSpanningTree(Edge* graph, int numEdges, int numVertexes);

int main() {
    int numVertexes;
    inputNumVertexes(&numVertexes);
    int numEdges;
    inputNumEdges(&numEdges, numVertexes);

    Edge* graph = malloc(sizeof(Edge) * numEdges);
    assert(graph);
    fillGraph(graph, numEdges, numVertexes);

    buildSpanningTree(graph, numEdges, numVertexes);

    free(graph);
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

void fillEdge(Edge* graph, int firstVert, int secondVert, int weightEdge, int index) {
    graph[index].firstVert = firstVert;
    graph[index].secondVert = secondVert;
    graph[index].weightEdge = weightEdge;
    graph[index].isEdgeInTree = false;
}

void fillGraph(Edge* graph, int numEdges, int numVertexes) {
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
        fillEdge(graph, firstVert, secondVert, weightEdge, i);
    }
}

void swap(Edge* pLeft, Edge* pRight) {
    Edge box = *pLeft;
    *pLeft = *pRight;
    *pRight = box;
}


void QuickSort(Edge* graph, int first, int last) {
    if (first < last) {
        int left = first, right = last;
        int middle = graph[(left + right) / 2].weightEdge;
        while (left < right) {
            while (graph[left].weightEdge < middle)
                ++left;
            while (graph[right].weightEdge > middle)
                --right;
            if (left <= right) {
                if (graph[left].weightEdge > graph[right].weightEdge)
                    swap(&graph[left], &graph[right]);
                ++left;
                --right;
            }
        }
        QuickSort(graph, first, right);
        QuickSort(graph, left, last);
    }
}

void printGraph(Edge* graph, int numEdges) {
    for (int i = 0; i < numEdges; ++i) {
        if (graph[i].isEdgeInTree == true)
            printf("%d %d \n", graph[i].firstVert, graph[i].secondVert);
    }
}

void fillParentAndRank(int* parent, int* rank, int numVertexes) {
    for (int i = 0; i < numVertexes; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int* parent, int vert) {
    if (vert == parent[vert])
        return vert;
    return find(parent, parent[vert]);
}

void unite(int* parent, int* rank, int parentFirst, int parentSecond) {
    if (rank[parentFirst] > rank[parentSecond]) {
        parent[parentSecond] = parentFirst;
    }
    else {
        parent[parentSecond] = parentFirst;
        if (rank[parentFirst] == rank[parentSecond])
            ++rank[parentFirst];
    }
}

void Kraskal(int* parent, int* rank, Edge* graph, int numEdges) {
    for (int i = 0; i < numEdges; ++i) {
        int firstVert = graph[i].firstVert - 1;
        int secondVert = graph[i].secondVert - 1;
        int parentFirst = find(parent, parent[firstVert]);
        int parentSecond = find(parent, parent[secondVert]);
        if (parentFirst != parentSecond) {
            unite(parent, rank, parentFirst, parentSecond);
            graph[i].isEdgeInTree = true;
        }
    }
}

bool isGraphConnected(int* parent, int numVertexes) {
    int sample = find(parent, 0);
    for (int i = 0; i < numVertexes; ++i) {
        if (sample != find(parent, i))
            return false;
    }
    return true;
}

void freeMemory(int* parent, int* rank) {
    free(parent);
    free(rank);
}

void buildSpanningTree(Edge* graph, int numEdges, int numVertexes) {
    QuickSort(graph, 0, numEdges - 1);

    int* parent = malloc(sizeof(int) * numVertexes);
    assert(parent);
    int* rank = malloc(sizeof(int) * numVertexes);
    assert(rank);
    fillParentAndRank(parent, rank, numVertexes);

    Kraskal(parent, rank, graph, numEdges);

    if (!isGraphConnected(parent, numVertexes)) {
        printf("no spanning tree");
        freeMemory(parent, rank);
        return;
    }
    printGraph(graph, numEdges);
    freeMemory(parent, rank);
}
