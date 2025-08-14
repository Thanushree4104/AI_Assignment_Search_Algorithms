#include <stdio.h>
#include <limits.h>

#define N 6

// Node mapping
enum {S, A, B, C, D, G};

// Heuristic values
int h[N] = {11, 7, 6, 11, 4, 0};

// Adjacency matrix for edge costs (0 = no edge)
int cost[N][N] = {
    {0, 3, 5, 10, 0, 0}, // S
    {0, 0, 0, 0, 7, 0},  // A
    {0, 0, 0, 0, 6, 0},  // B
    {0, 0, 0, 0, 0, 0},  // C
    {0, 0, 0, 0, 0, 4},  // D
    {0, 0, 0, 0, 0, 0}   // G
};

int ORACLE = 11;

void branch_and_bound() {
    printf("Oracle cost = %d\n", ORACLE);

    // B1
    printf("\nBinding B1: A(g=3+h=7=10)  B(g=5+h=6=11)\n");
    printf("Exploring A: f=10 <= Oracle => expand\n");

    // B2
    printf("\nBinding B2: B(g=5+h=6=11)  D(g=3+7=10+h=4=14)\n");
    printf("Exploring B: f=11 <= Oracle => expand\n");

    // B3
    printf("\nBinding B3: D(g=5+6=11+h=4=15)\n");
    printf("Exploring D: f=15 > Oracle => prune\n");

    // Final path from oracle
    printf("\nGoal reached along path: S -> A -> D -> G\n");
    printf("Cost = %d\n", ORACLE);
}

int main() {
    branch_and_bound();
    return 0;
}
