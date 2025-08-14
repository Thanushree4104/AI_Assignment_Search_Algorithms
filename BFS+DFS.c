#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define N 7

// Fixed node order for lexicographic comparisons
static const char nodes[N] = {'S','A','B','C','D','E','G'};
int adj[N][N];

// Map label -> index
int idx(char c){ for(int i=0;i<N;i++) if(nodes[i]==c) return i; return -1; }

void addEdge(char u, char v){
    int ui = idx(u), vi = idx(v);
    adj[ui][vi] = adj[vi][ui] = 1;
}

// BFS reachability that FORBIDS using any node marked in forbidden[]
// (except the BFS start itself)
bool bfs_reachable(int start, int goal, const bool forbidden[N]){
    bool seen[N] = {0};
    int q[N], f=0, r=0;

    // local forbidden copy so we can allow 'start'
    bool ban[N]; memcpy(ban, forbidden, sizeof(ban));
    ban[start] = false;

    if(ban[start]) return false; // (defensive) shouldn't happen now

    seen[start] = true; q[r++] = start;

    while(f<r){
        int u = q[f++];
        if(u == goal) return true;
        for(int v=0; v<N; v++){
            if(adj[u][v] && !seen[v] && !ban[v]){
                seen[v] = true; q[r++] = v;
            }
        }
    }
    return false;
}

// Path + in-path markers
int path[N], plen = 0;
bool inPath[N] = {0};

// DFS that at each step picks the lexicographically smallest neighbor
// whose BFS-reachability (without reusing current-path nodes) is TRUE.
bool dfs_hybrid(int u, int goal){
    path[plen++] = u;
    inPath[u] = true;

    if(u == goal){
        // print final path once
        printf("Final Path: ");
        for(int i=0;i<plen;i++){
            printf("%c", nodes[path[i]]);
            if(i+1<plen) printf(" -> ");
        }
        printf("\n");
        return true;
    }

    // collect neighbors (unvisited in current path)
    int neigh[N], cnt=0;
    for(int v=0; v<N; v++){
        if(adj[u][v] && !inPath[v]) neigh[cnt++] = v;
    }

    // sort neighbors by label for lexicographic order
    for(int i=0;i<cnt-1;i++)
        for(int j=i+1;j<cnt;j++)
            if(nodes[neigh[i]] > nodes[neigh[j]]){
                int t = neigh[i]; neigh[i] = neigh[j]; neigh[j] = t;
            }

    // try neighbors greedily
    for(int i=0;i<cnt;i++){
        int v = neigh[i];
        if(bfs_reachable(v, goal, inPath)){
            if(dfs_hybrid(v, goal)) return true; // preemptive exit on success
        }
        
    }

    // backtrack
    inPath[u] = false;
    plen--;
    return false;
}

int main(void){
    memset(adj, 0, sizeof(adj));

    // Base graph edges (undirected)
    addEdge('S','A');
    addEdge('S','B');
    addEdge('A','B');
    addEdge('A','D');
    addEdge('B','C');
    addEdge('C','E');
    addEdge('D','G');

    int S = idx('S'), G = idx('G');


    if(!dfs_hybrid(S, G)){
        printf("No path found.\n");
    }
    return 0;
}
