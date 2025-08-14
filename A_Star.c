#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 7
#define INF 1000000000

char name[N] = {'S','A','B','C','D','E','G'};

int adj[N][N] = {
    {   0,   3,   5, INF, INF, INF, INF }, // S
    {   3,   0,   4, INF,   3, INF, INF }, // A
    {   5,   4,   0,   4, INF, INF, INF }, // B
    { INF, INF,   4,   0, INF,   6, INF }, // C
    { INF,   3, INF, INF,   0, INF,   5 }, // D
    { INF, INF, INF,   6, INF,   0, INF }, // E
    { INF, INF, INF, INF,   5, INF,   0 }  // G
};

int true_dist[N];   // True distances from each node to goal
int h[N];           // Heuristic used by A*

void dijkstra_to_goal(int goal) {
    int dist[N], used[N] = {0};
    for (int i = 0; i < N; ++i) dist[i] = INF;
    dist[goal] = 0;

    for (int iter = 0; iter < N; ++iter) {
        int u = -1;
        for (int i = 0; i < N; ++i)
            if (!used[i] && (u == -1 || dist[i] < dist[u])) u = i;

        if (u == -1 || dist[u] == INF) break;
        used[u] = 1;

        for (int v = 0; v < N; ++v) {
            if (adj[u][v] < INF && dist[v] > dist[u] + adj[u][v])
                dist[v] = dist[u] + adj[u][v];
        }
    }

    for (int i = 0; i < N; ++i)
        true_dist[i] = dist[i];
}

int pick_min_f(int open[], int g[]) {
    int best = -1;
    for (int i = 0; i < N; ++i) {
        if (!open[i]) continue;
        int f = g[i] + h[i];
        if (best == -1 || f < g[best] + h[best] || 
           (f == g[best] + h[best] && g[i] < g[best]) ||
           (f == g[best] + h[best] && g[i] == g[best] && i < best)) {
            best = i;
        }
    }
    return best;
}

int reconstruct_path(int parent[], int out[]) {
    int tmp[N], t = 0;
    int cur = N - 1;
    while (cur != -1 && t < N) {
        tmp[t++] = cur;
        cur = parent[cur];
    }
    int len = 0;
    for (int i = t - 1; i >= 0; --i) out[len++] = tmp[i];
    return len;
}

void a_star_with_oracle(int start, int goal, int oracle) {
    dijkstra_to_goal(goal);
    for (int i = 0; i < N; ++i)
        h[i] = (true_dist[i] >= INF) ? INF : true_dist[i];

    if (oracle >= 0)
        printf("Oracle bound: %d\n", oracle);
    else
        printf("Running full A* (no oracle bound)\n");

    int g[N], parent[N], open[N], closed[N], best_g[N];
    for (int i = 0; i < N; ++i) {
        g[i] = INF; parent[i] = -1;
        open[i] = closed[i] = 0;
        best_g[i] = INF;
    }

    g[start] = 0;
    open[start] = 1;
    best_g[start] = 0;

    int step = 0;

    while (1) {
        int u = pick_min_f(open, g);
        if (u == -1) {
            printf("No nodes left in open set. Failed.\n");
            return;
        }

        int fu = g[u] + h[u];

        if (oracle >= 0 && fu > oracle) {
            printf("Node %c: f=%d > oracle %d. Terminating.\n", name[u], fu, oracle);
            return;
        }

        open[u] = 0;
        closed[u] = 1;

        printf("\nStep %d: Expand %c (g=%d, f=%d)\n", ++step, name[u], g[u], fu);

        if (u == goal) {
            int path[N], len = reconstruct_path(parent, path);
            printf("\n✅ Goal reached! Path: ");
            for (int i = 0; i < len; ++i)
                printf("%c%s", name[path[i]], (i + 1 < len ? " -> " : ""));
            printf("\nTotal cost: %d\n", g[goal]);
            return;
        }

        for (int v = 0; v < N; ++v) {
            if (adj[u][v] >= INF || closed[v]) continue;

            int tentative_g = g[u] + adj[u][v];
            int tentative_f = (h[v] >= INF) ? INF : (tentative_g + h[v]);

            if (tentative_g >= best_g[v]) continue;
            if (oracle >= 0 && tentative_f > oracle) continue;

            best_g[v] = tentative_g;
            g[v] = tentative_g;
            parent[v] = u;
            open[v] = 1;

            printf("  → Consider %c: g=%d, f=%d\n", name[v], tentative_g, tentative_f);
        }
    }
}

int main(void) {
    int start = 0; // 'S'
    int goal = 6;  // 'G'
    int oracle = 11;  // Set to -1 for full A*

    a_star_with_oracle(start, goal, oracle);

    return 0;
}
