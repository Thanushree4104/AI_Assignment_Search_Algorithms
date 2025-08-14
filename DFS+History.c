#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define N 7

static const char nodes[N] = {'S','A','B','C','D','E','G'};
int adj[N][N];

// Map label -> index
int idx(char c){ for(int i=0;i<N;i++) if(nodes[i]==c) return i; return -1; }

void addEdge(char u, char v){
    int ui = idx(u), vi = idx(v);
    adj[ui][vi] = adj[vi][ui] = 1;
}

int path[N], plen = 0;
bool inPath[N] = {0};
bool explored[N] = {0}; // history of globally explored nodes

bool dfs_with_history(int u, int goal){
    path[plen++] = u;
    inPath[u] = true;

    if(u == goal){
        printf("Final Path: ");
        for(int i=0;i<plen;i++){
            printf("%c", nodes[path[i]]);
            if(i+1<plen) printf(" -> ");
        }
        printf("\n");
        return true;
    }

    // collect neighbors not in path and not already explored globally
    int neigh[N], cnt=0;
    for(int v=0; v<N; v++){
        if(adj[u][v] && !inPath[v] && !explored[v]) neigh[cnt++] = v;
    }

    // sort lexicographically
    for(int i=0;i<cnt-1;i++)
        for(int j=i+1;j<cnt;j++)
            if(nodes[neigh[i]] > nodes[neigh[j]]){
                int t = neigh[i]; neigh[i] = neigh[j]; neigh[j] = t;
            }

    // explore neighbors greedily
    for(int i=0;i<cnt;i++){
        int v = neigh[i];
        if(dfs_with_history(v, goal)) return true;
        explored[v] = true; // mark as explored in history after returning
    }

    inPath[u] = false;
    plen--;
    return false;
}

int main(void){
    memset(adj, 0, sizeof(adj));

    // Base graph edges
    addEdge('S','A');
    addEdge('S','B');
    addEdge('A','B');
    addEdge('A','D');
    addEdge('B','C');
    addEdge('C','E');
    addEdge('D','G');

    int S = idx('S'), G = idx('G');

    if(!dfs_with_history(S, G)){
        printf("No path found.\n");
    }
    return 0;
}
