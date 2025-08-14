#include <stdio.h>
#include <string.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int deadend[MAX];
int path[MAX];
int pathIndex = 0;
int n = 7; // Nodes: S=0, A=1, B=2, C=3, D=4, E=5, G=6

char nodeName[] = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};

void printPath() {
    for (int i = 0; i < pathIndex; i++) {
        printf("%c", nodeName[path[i]]);
        if (i < pathIndex - 1) printf(" -> ");
    }
    printf("\n");
}

void BMS(int current, int goal) {
    visited[current] = 1;
    path[pathIndex++] = current;

    if (current == goal) {
        printPath();
    } else {
        int hasNext = 0;
        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !visited[i] && !deadend[i]) {
                hasNext = 1;
                BMS(i, goal);
            }
        }

        if (!hasNext && current != goal) {
            deadend[current] = 1;
            printf("%c marked as DEADEND and removed.\n", nodeName[current]);
        }
    }

    pathIndex--;
    visited[current] = 0; // backtrack
}

int main() {
    memset(graph, 0, sizeof(graph));
    memset(visited, 0, sizeof(visited));
    memset(deadend, 0, sizeof(deadend));

    // Hardcoding edges from the given base graph
    graph[0][1] = graph[1][0] = 1; // S-A
    graph[0][2] = graph[2][0] = 1; // S-B
    graph[1][4] = graph[4][1] = 1; // A-D
    graph[1][2] = graph[2][1] = 1; // A-B
    graph[2][3] = graph[3][2] = 1; // B-C
    graph[3][5] = graph[5][3] = 1; // C-E
    graph[4][6] = graph[6][4] = 1; // D-G

    printf("British Museum Search Paths:\n");
    BMS(0, 6); // Start at S (0), goal G (6)

    return 0;
}
