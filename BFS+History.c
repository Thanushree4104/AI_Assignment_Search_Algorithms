#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VERTICES 10

char vertices[MAX_VERTICES];
int adj[MAX_VERTICES][MAX_VERTICES];
int vertexCount = 0;
bool visited[MAX_VERTICES];
int parent[MAX_VERTICES];

int getIndex(char v) {
    for (int i = 0; i < vertexCount; i++)
        if (vertices[i] == v) return i;
    return -1;
}

void addVertex(char v) {
    if (getIndex(v) == -1) {
        vertices[vertexCount++] = v;
    }
}

void addEdge(char src, char dest) {
    addVertex(src);
    addVertex(dest);
    int i = getIndex(src);
    int j = getIndex(dest);
    adj[i][j] = 1;
    adj[j][i] = 1;
}

void bfsHistory(char start, char goal) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    memset(visited, false, sizeof(visited));
    memset(parent, -1, sizeof(parent));

    int startIndex = getIndex(start);
    int goalIndex = getIndex(goal);

    visited[startIndex] = true;
    queue[rear++] = startIndex;

    while (front < rear) {
        int current = queue[front++];

        if (current == goalIndex)
            break;

        // Collect neighbors in lexicographic order
        char neighbors[MAX_VERTICES];
        int idxList[MAX_VERTICES];
        int count = 0;

        for (int i = 0; i < vertexCount; i++) {
            if (adj[current][i] && !visited[i]) {
                neighbors[count] = vertices[i];
                idxList[count] = i;
                count++;
            }
        }

        // Sort neighbors lexicographically
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (neighbors[i] > neighbors[j]) {
                    char tempC = neighbors[i];
                    neighbors[i] = neighbors[j];
                    neighbors[j] = tempC;

                    int tempI = idxList[i];
                    idxList[i] = idxList[j];
                    idxList[j] = tempI;
                }
            }
        }

        // Push neighbors into queue
        for (int i = 0; i < count; i++) {
            int next = idxList[i];
            visited[next] = true; // history: mark globally visited
            parent[next] = current;
            queue[rear++] = next;
        }
    }

    // Print final path
    int path[MAX_VERTICES];
    int len = 0;
    for (int v = goalIndex; v != -1; v = parent[v]) {
        path[len++] = v;
    }
    printf("Final Path: ");
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", vertices[path[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

int main() {
    // Base graph
    addEdge('S', 'A');
    addEdge('S', 'B');
    addEdge('A', 'B');
    addEdge('A', 'D');
    addEdge('B', 'C');
    addEdge('C', 'E');
    addEdge('D', 'G');

    bfsHistory('S', 'G');
    return 0;
}
