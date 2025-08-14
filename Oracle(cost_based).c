#include <stdio.h>
#include <limits.h>

#define N 7  // Number of nodes

int costMatrix[N][N] = {
    // S   A   B   C   D   E   G
    { 0,  4,  3,  0,  0,  0,  0}, // S
    { 0,  0,  0,  0,  3,  0,  0}, // A
    { 0,  0,  0,  7,  0,  4,  0}, // B
    { 0,  0,  0,  0,  0,  6,  0}, // C
    { 0,  0,  0,  0,  0,  0,  4}, // D
    { 0,  0,  0,  0,  0,  0,  7}, // E
    { 0,  0,  0,  0,  0,  0,  0}  // G
};

char nodeNames[N] = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};

int bestCost = INT_MAX;
char bestPath[100];
char currentPath[100];

void dfs(int current, int goal, int cost, int depth) {
    currentPath[depth] = nodeNames[current];
    if (current == goal) {
        currentPath[depth + 1] = '\0';
        if (cost < bestCost) {
            bestCost = cost;
            for (int i = 0; i <= depth; i++)
                bestPath[i] = currentPath[i];
            bestPath[depth + 1] = '\0';
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (costMatrix[current][i] > 0) {
            dfs(i, goal, cost + costMatrix[current][i], depth + 1);
        }
    }
}

int main() {
    int start = 0; // S
    int goal = 6;  // G
    dfs(start, goal, 0, 0);

    printf("Best Path: ");
    for (int i = 0; bestPath[i] != '\0'; i++) {
        printf("%c", bestPath[i]);
        if (bestPath[i + 1] != '\0')
            printf(" -> ");
    }
    printf("\nCost: %d\n", bestCost);

    return 0;
}
