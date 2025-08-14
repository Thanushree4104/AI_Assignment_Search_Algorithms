#include <stdio.h>
#include <string.h>

#define MAX 10

// Graph adjacency matrix
int graph[MAX][MAX];
char vertices[MAX] = {'S','A','B','C','D','E','G'};
int vCount = 7;

// Heuristic values for each vertex
int heuristic[] = {8, 3, 5, 7, 2, 6, 0}; 
// S=8, A=3, B=5, C=7, D=2, E=6, G=0

int visited[MAX];

int getIndex(char c) {
    for (int i = 0; i < vCount; i++)
        if (vertices[i] == c) return i;
    return -1;
}

void addEdge(char u, char v) {
    int i = getIndex(u);
    int j = getIndex(v);
    graph[i][j] = graph[j][i] = 1;
}

void hillClimbWithHistory(char start, char goal) {
    int path[MAX], pathLen = 0;
    int current = getIndex(start);
    int goalIndex = getIndex(goal);

    memset(visited, 0, sizeof(visited));

    path[pathLen++] = current;
    visited[current] = 1;

    while (current != goalIndex) {
        int nextNode = -1;
        int minH = 999;

        // Choose neighbor with smallest heuristic (not visited)
        for (int i = 0; i < vCount; i++) {
            if (graph[current][i] && !visited[i]) {
                if (heuristic[i] < minH) {
                    minH = heuristic[i];
                    nextNode = i;
                }
            }
        }

        if (nextNode == -1) {
            printf("No path found!\n");
            return;
        }

        current = nextNode;
        path[pathLen++] = current;
        visited[current] = 1;
    }

    printf("Final Path: ");
    for (int i = 0; i < pathLen; i++) {
        printf("%c", vertices[path[i]]);
        if (i < pathLen - 1) printf(" -> ");
    }
    printf("\n");
}

int main() {
    memset(graph, 0, sizeof(graph));

    // Add edges
    addEdge('S','A');
    addEdge('S','B');
    addEdge('A','B');
    addEdge('A','D');
    addEdge('B','C');
    addEdge('C','E');
    addEdge('D','G');

    hillClimbWithHistory('S', 'G');

    return 0;
}
