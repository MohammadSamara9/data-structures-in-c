/*
 * Lecture 16 - Graphs
 * Bellman-Ford: shortest paths from one source, and it works with
 * NEGATIVE edge weights (Dijkstra does not).
 *
 * The slides give this as PSEUDOCODE; this file is my C version of it:
 *
 *   function bellmanFord(G, S)
 *     for each vertex V in G
 *       distance[V] <- infinite
 *       previous[V] <- NULL
 *     distance[S] <- 0
 *     for each vertex V in G                    (repeat |V| - 1 times)
 *       for each edge (U,V) in G
 *         tempDistance <- distance[U] + edge_weight(U, V)
 *         if tempDistance < distance[V]
 *           distance[V] <- tempDistance
 *           previous[V] <- U
 *     for each edge (U,V) in G
 *       if distance[U] + edge_weight(U, V) < distance[V]
 *         Error: Negative Cycle Exists
 *     return distance[], previous[]
 *
 * Time: O(V * E)
 */
#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
#define NONE -1

typedef struct {
    int u, v, weight;
} Edge;

/* Returns 1 on success, 0 if a negative cycle exists */
int bellmanFord(Edge edges[], int E, int V, int S, int distance[], int previous[]) {
    for (int i = 0; i < V; i++) {
        distance[i] = INF;
        previous[i] = NONE;
    }
    distance[S] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int U = edges[j].u, W = edges[j].v;
            if (distance[U] == INF) /* cannot reach U yet */
                continue;
            int tempDistance = distance[U] + edges[j].weight;
            if (tempDistance < distance[W]) {
                distance[W] = tempDistance;
                previous[W] = U;
            }
        }
    }

    for (int j = 0; j < E; j++) {
        int U = edges[j].u, W = edges[j].v;
        if (distance[U] != INF && distance[U] + edges[j].weight < distance[W])
            return 0; /* Negative Cycle Exists */
    }
    return 1;
}

void printPath(int previous[], int v, const char names[]) {
    if (previous[v] != NONE) {
        printPath(previous, previous[v], names);
        printf(" -> ");
    }
    printf("%c", names[v]);
}

int main(void) {
    const char names[] = "SABCDE";
    int V = 6;
    /* a directed graph with some negative edges (but no negative cycle) */
    Edge edges[] = {
        {0, 1, 10}, {0, 5, 8}, {1, 3, 2}, {2, 1, 1},
        {3, 2, -2}, {4, 1, -4}, {4, 3, -1}, {5, 4, 1}
    };
    int E = sizeof(edges) / sizeof(edges[0]);
    int distance[6], previous[6];

    if (!bellmanFord(edges, E, V, 0, distance, previous)) {
        printf("Error: Negative Cycle Exists\n");
        return 1;
    }

    printf("Shortest paths from S:\n");
    for (int v = 0; v < V; v++) {
        printf("  %c: distance %3d   path ", names[v], distance[v]);
        printPath(previous, v, names);
        printf("\n");
    }

    /* now add an edge that makes a negative cycle: B -> S with weight -20 */
    Edge withCycle[9];
    for (int i = 0; i < E; i++)
        withCycle[i] = edges[i];
    withCycle[E] = (Edge){1, 0, -20};
    if (!bellmanFord(withCycle, E + 1, V, 0, distance, previous))
        printf("\nAfter adding B -> S (-20): Error: Negative Cycle Exists\n");

    return 0;
}
