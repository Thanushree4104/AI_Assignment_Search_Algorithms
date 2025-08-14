#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20

char nodes[] = {'S','A','B','C','D','E','G'};
int n = 7;
int adj[MAX][MAX];
int visited[MAX];
int parent[MAX];
int idx(char v) {
    for (int i = 0; i < n; ++i) if (nodes[i] == v) return i;
    return -1;
}

int cmpNodes(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return nodes[ia] - nodes[ib];
}

void bfsGreedy(int start, int goal) {
    int queue[MAX], front = 0, rear = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++) parent[i] = -1;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];

        if (u == goal) {
            // reconstruct path
            int path[MAX], len = 0;
            for (int v = goal; v != -1; v = parent[v]) {
                path[len++] = v;
            }
            printf("Final Path: ");
            for (int i = len - 1; i >= 0; --i) {
                printf("%c", nodes[path[i]]);
                if (i > 0) printf(" -> ");
            }
            printf("\n");
            return; // preemptive exit
        }

        // collect unvisited neighbors
        int neighbors[MAX], cnt = 0;
        for (int v = 0; v < n; ++v) {
            if (adj[u][v] && !visited[v]) {
                neighbors[cnt++] = v;
            }
        }

        // sort neighbors lexicographically
        if (cnt > 1) qsort(neighbors, cnt, sizeof(int), cmpNodes);

        // enqueue neighbors
        for (int i = 0; i < cnt; ++i) {
            visited[neighbors[i]] = 1;
            parent[neighbors[i]] = u;
            queue[rear++] = neighbors[i];
        }
    }

    printf("No path found from %c to %c.\n", nodes[start], nodes[goal]);
}

int main() {
    memset(adj, 0, sizeof(adj));

    int S = idx('S'), A = idx('A'), B = idx('B'), C = idx('C'),
        D = idx('D'), E = idx('E'), G = idx('G');

    // Base graph edges
    adj[S][A] = adj[A][S] = 1; // S-A
    adj[S][B] = adj[B][S] = 1; // S-B
    adj[A][B] = adj[B][A] = 1; // A-B
    adj[A][D] = adj[D][A] = 1; // A-D
    adj[B][C] = adj[C][B] = 1; // B-C
    adj[C][E] = adj[E][C] = 1; // C-E
    adj[D][G] = adj[G][D] = 1; // D-G

    bfsGreedy(S, G);
    return 0;
}
