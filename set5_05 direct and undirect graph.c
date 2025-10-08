#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int n, adj[MAX][MAX];
int visited[MAX], stack[MAX], stackPos, cycleCount = 0;

int smallestCycle = MAX, largestCycle = -1;

// Utility function to print a cycle
void printCycle(int start) {
    int cycleSize = 0;
    printf("Cycle: ");
    for (int i = stackPos - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
        cycleSize++;
        if (stack[i] == start) break;
    }
    printf("\n");

    if (cycleSize < smallestCycle) smallestCycle = cycleSize;
    if (cycleSize > largestCycle) largestCycle = cycleSize;
}

// DFS to detect and track cycles
void DFS(int u) {
    visited[u] = 1;
    stack[stackPos++] = u;

    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                DFS(v);
            } else {
                // back edge found → cycle
                for (int i = 0; i < stackPos; i++) {
                    if (stack[i] == v) {
                        cycleCount++;
                        printCycle(v);
                        break;
                    }
                }
            }
        }
    }

    stackPos--;
    visited[u] = 0; // allow other paths to find cycles
}

int main() {
    int e, u, v;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Init adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d%d", &u, &v);
        adj[u][v] = 1; // directed graph
        // For undirected: adj[u][v] = adj[v][u] = 1;
    }

    for (int i = 0; i < n; i++) visited[i] = 0;

    // Run DFS from each node
    for (int i = 0; i < n; i++) {
        DFS(i);
    }

    if (cycleCount == 0) {
        printf("No cycles found.\n");
    } else {
        printf("\nTotal Cycles: %d\n", cycleCount);
        printf("Smallest Cycle Length: %d\n", smallestCycle);
        printf("Largest Cycle Length: %d\n", largestCycle);
    }

    return 0;
}
