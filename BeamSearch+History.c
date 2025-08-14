#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 7
#define BEAM_WIDTH 2

// Node indices: S=0, A=1, B=2, C=3, D=4, E=5, G=6
char *names[] = {"S", "A", "B", "C", "D", "E", "G"};
int heuristic[] = {6, 7, 6, 7, 3, 4, 0};

int graph[N][N] = {
    // S   A   B   C   D   E   G
    {0,  3,  5,  0,  0,  0,  0}, // S
    {3,  0,  4,  0,  5,  0,  0}, // A
    {5,  4,  0,  4,  0,  0,  0}, // B
    {0,  0,  4,  0,  0,  6,  0}, // C
    {0,  0,  0,  0,  0,  0,  3}, // D
    {0,  0,  0,  6,  0,  0,  0}, // E
    {0,  0,  0,  0,  3,  0,  0}  // G
};

typedef struct {
    int node;
    int cost;
    int path[20];
    int path_len;
} State;

// Copy state helper
void copy_state(State *dest, const State *src) {
    dest->node = src->node;
    dest->cost = src->cost;
    dest->path_len = src->path_len;
    for (int i = 0; i < src->path_len; i++) {
        dest->path[i] = src->path[i];
    }
}

int main() {
    int visited_global[N] = {0}; // global history of expansions
    State frontier[50], new_frontier[50];
    int frontier_size = 0, new_size;

    // Initialize with start node S (0)
    State start_state = {0, 0, {0}, 1};
    frontier[frontier_size++] = start_state;
    visited_global[0] = 1;

    while (frontier_size > 0) {
        // Check if any frontier state is goal
        for (int i = 0; i < frontier_size; i++) {
            if (frontier[i].node == 6) { // G = 6
                printf("Path: ");
                for (int j = 0; j < frontier[i].path_len; j++) {
                    printf("%s", names[frontier[i].path[j]]);
                    if (j < frontier[i].path_len - 1) printf("-");
                }
                printf("\nTotal distance: %d\n", frontier[i].cost);
                return 0;
            }
        }

        new_size = 0;

        // Expand each state in the current frontier
        for (int i = 0; i < frontier_size; i++) {
            State curr = frontier[i];
            for (int nb = 0; nb < N; nb++) {
                if (graph[curr.node][nb] && !visited_global[nb]) {
                    State child;
                    copy_state(&child, &curr);
                    child.node = nb;
                    child.cost += graph[curr.node][nb];
                    child.path[child.path_len++] = nb;

                    new_frontier[new_size++] = child;
                    visited_global[nb] = 1;
                }
            }
        }

        // Sort new_frontier by heuristic (ascending)
        for (int i = 0; i < new_size - 1; i++) {
            for (int j = i + 1; j < new_size; j++) {
                if (heuristic[new_frontier[j].node] < heuristic[new_frontier[i].node]) {
                    State tmp = new_frontier[i];
                    new_frontier[i] = new_frontier[j];
                    new_frontier[j] = tmp;
                }
            }
        }

        // Keep only top BEAM_WIDTH states
        frontier_size = (new_size < BEAM_WIDTH ? new_size : BEAM_WIDTH);
        for (int i = 0; i < frontier_size; i++) {
            frontier[i] = new_frontier[i];
        }
    }

    printf("Goal not found.\n");
    return 0;
}
