#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

// Graph representation
char nodes[] = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};
int numNodes = 7;

// Adjacency matrix
int adj[MAX][MAX];

// Heuristic values
int heuristic[] = {7, 4, 6, 7, 3, 6, 0};

// Beam width
int beamWidth = 2;

// Find index of a node
int getIndex(char c) {
    for (int i = 0; i < numNodes; i++)
        if (nodes[i] == c)
            return i;
    return -1;
}

// Add edge between two nodes
void addEdge(char u, char v) {
    int i = getIndex(u);
    int j = getIndex(v);
    adj[i][j] = 1;
    adj[j][i] = 1;
}

// Sort by heuristic
void sortByHeuristic(int arr[], int *size) {
    for (int i = 0; i < *size - 1; i++) {
        for (int j = i + 1; j < *size; j++) {
            if (heuristic[arr[i]] > heuristic[arr[j]]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Beam search algorithm
void beamSearch(char start, char goal) {
    int visited[MAX] = {0};
    int queue[MAX];
    int qSize = 0;

    int path[MAX];
    int pathSize = 0;

    int startIdx = getIndex(start);
    int goalIdx = getIndex(goal);

    queue[qSize++] = startIdx;
    visited[startIdx] = 1;
    path[pathSize++] = startIdx;

    while (qSize > 0) {
        // If goal found
        if (queue[0] == goalIdx) {
            printf("Final Path: ");
            for (int i = 0; i < pathSize; i++) {
                printf("%c", nodes[path[i]]);
                if (i != pathSize - 1) printf(" -> ");
            }
            printf("\nBeam Width: %d\n", beamWidth);
            return;
        }

        // Expand current level
        int nextLevel[MAX];
        int nextSize = 0;

        for (int i = 0; i < qSize; i++) {
            int node = queue[i];
            for (int j = 0; j < numNodes; j++) {
                if (adj[node][j] && !visited[j]) {
                    nextLevel[nextSize++] = j;
                    visited[j] = 1;
                }
            }
        }

        // Sort candidates by heuristic and take top beamWidth
        sortByHeuristic(nextLevel, &nextSize);
        if (nextSize > beamWidth) nextSize = beamWidth;

        // Add to path (only picking first of beam as actual path choice)
        path[pathSize++] = nextLevel[0];

        // Prepare next queue
        memcpy(queue, nextLevel, nextSize * sizeof(int));
        qSize = nextSize;
    }
}

int main() {
    memset(adj, 0, sizeof(adj));

    // Base graph
    addEdge('S', 'A');
    addEdge('S', 'B');
    addEdge('A', 'B');
    addEdge('A', 'D');
    addEdge('B', 'C');
    addEdge('C', 'E');
    addEdge('D', 'G');

    beamSearch('S', 'G');
    return 0;
}
