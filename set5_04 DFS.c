#include <stdio.h>

#define MAX 20

int adj[MAX][MAX], visited[MAX], start[MAX], finish[MAX], time = 0, n;

// DFS function
void DFS(int u) {
    visited[u] = 1;
    start[u] = ++time;

    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFS(v);
            } else if (finish[v] == 0) {
                printf("Back Edge: %d -> %d\n", u, v);
            } else if (start[u] < start[v]) {
                printf("Forward Edge: %d -> %d\n", u, v);
            } else {
                printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }

    finish[u] = ++time;
}

int main() {
    int e, u, v;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d%d", &u, &v);
        adj[u][v] = 1; // directed graph
    }

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        start[i] = finish[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i])
            DFS(i);
    }

    return 0;
}
