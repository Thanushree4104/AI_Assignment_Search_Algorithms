#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define N 7

char nodes[N] = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};
int adj[N][N] = {0};

// Adjusted heuristics so B is preferred from S
int heuristic[N] = {
    8, // S
    5, // A
    3, // B
    7, // C
    2, // D
    6, // E
    0  // G
};

int getIndex(char node) {
    for (int i = 0; i < N; i++)
        if (nodes[i] == node) return i;
    return -1;
}

void addEdge(char u, char v) {
    int ui = getIndex(u);
    int vi = getIndex(v);
    adj[ui][vi] = 1;
    adj[vi][ui] = 1; // undirected
}

void hillClimbNoHistory(char start, char goal) {
    int current = getIndex(start);
    printf("Path: %c", nodes[current]);

    while (nodes[current] != goal) {
        int next = -1;
        int bestHeuristic = INT_MAX;

        for (int i = 0; i < N; i++) {
            if (adj[current][i] && heuristic[i] < bestHeuristic) {
                next = i;
                bestHeuristic = heuristic[i];
            }
        }

        if (next == -1) {
            printf("\nNo path found.\n");
            return;
        }

        current = next;
        printf(" -> %c", nodes[current]);
    }

    printf("\n");
}

int main() {
    // Graph from your base example
    addEdge('S','A');
    addEdge('S','B');
    addEdge('A','B');
    addEdge('A','D');
    addEdge('B','C');
    addEdge('C','E');
    addEdge('D','G');

    hillClimbNoHistory('S', 'G');
    return 0;
}
