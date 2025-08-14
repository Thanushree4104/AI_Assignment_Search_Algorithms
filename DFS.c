#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20
char nodes[] = {'S','A','B','C','D','E','G'};
int n = 7;
int adj[MAX][MAX];
int visited[MAX];
int path[MAX], pathLen = 0;
int found = 0;
int idx(char v) {
    for (int i = 0; i < n; ++i) if (nodes[i] == v) return i;
    return -1;
}

// comparator for qsort on neighbor indices, by node letter 
int cmpNeighbors(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (nodes[ia] - nodes[ib]);
}

/* Greedy DFS: pick lexicographically smallest unvisited neighbor first.
   Print the final path once target is reached and immediately stop. */
void dfsGreedy(int u, int target) {
    if (found) return;

    visited[u] = 1;
    path[pathLen++] = u;

    if (u == target) {
        /* Print only the final found path */
        printf("Final Path: ");
        for (int i = 0; i < pathLen; ++i) {
            printf("%c", nodes[path[i]]);
            if (i + 1 < pathLen) printf(" -> ");
        }
        printf("\n");
        found = 1;
        return;
    }

    /* collect unvisited neighbors */
    int neighbors[MAX], cnt = 0;
    for (int v = 0; v < n; ++v) {
        if (adj[u][v] && !visited[v]) {
            neighbors[cnt++] = v;
        }
    }

    /* sort neighbors lexicographically by node label */
    if (cnt > 1) qsort(neighbors, cnt, sizeof(int), cmpNeighbors);

    /* explore greedily */
    for (int i = 0; i < cnt && !found; ++i) {
        dfsGreedy(neighbors[i], target);
    }

    /* normal backtrack: unmark visited for this node so siblings can use it */
    visited[u] = 0;
    --pathLen;
}

int main() {
    memset(adj, 0, sizeof(adj));
    memset(visited, 0, sizeof(visited));

    /* Hardcode edges (undirected) for your base graph */
    int S = idx('S'), A = idx('A'), B = idx('B'), C = idx('C'), D = idx('D'), E = idx('E'), G = idx('G');

    adj[S][A] = adj[A][S] = 1; // S-A
    adj[S][B] = adj[B][S] = 1; // S-B
    adj[A][B] = adj[B][A] = 1; // A-B
    adj[A][D] = adj[D][A] = 1; // A-D
    adj[B][C] = adj[C][B] = 1; // B-C
    adj[C][E] = adj[E][C] = 1; // C-E
    adj[D][G] = adj[G][D] = 1; // D-G

    /* run greedy DFS from S to G */
    dfsGreedy(S, G);

    if (!found) {
        printf("No path found from S to G.\n");
    }
    return 0;
}
