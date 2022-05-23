#include "input.h"
#include "graph.h"

int main() {
    int numVertexes = InputNumVertexes();
    int numEdges = InputNumEdges(numVertexes);
    int** graph = InputGraph(numEdges, numVertexes);
    BuildMST(graph, numVertexes);
    FreeGraph(graph, numVertexes);
    return 0;
}
