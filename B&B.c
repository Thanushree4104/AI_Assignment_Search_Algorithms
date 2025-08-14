#include <stdio.h>

// Struct to store a bounding box entry
typedef struct {
    char name;
    int g;
} Entry;

// Function to print a bounding box
void printBoundingBox(int boxNum, Entry entries[], int size) {
    printf("Bounding Box B%d: ", boxNum);
    for (int i = 0; i < size; i++) {
        printf("%c(g=%d)", entries[i].name, entries[i].g);
        if (i < size - 1) printf(" ");
    }
    printf("\n");
}

// Function to simulate exploration
void explore(char node, int g, int *oracle) {
    printf("Exploring %c: g=%d < Oracle=%d\n", node, g, *oracle);
}

int main() {
    int oracle = 11;

    printf("Starting simulation...\n");

    // B1
    Entry B1[] = { {'A', 3}, {'B', 6} };
    printBoundingBox(1, B1, 2);
    explore('A', 3, &oracle);

    // B2
    Entry B2[] = { {'B', 6}, {'B', 7}, {'D', 8} };
    printBoundingBox(2, B2, 3);
    explore('B', 6, &oracle);

    // B3
    Entry B3[] = { {'A', 9}, {'C', 9}, {'B', 7}, {'D', 8} };
    printBoundingBox(3, B3, 4);
    explore('B', 7, &oracle);

    // B4
    Entry B4[] = { {'C', 11}, {'D', 8}, {'A', 9}, {'C', 9} };
    printBoundingBox(4, B4, 4);
    explore('D', 8, &oracle);

    // Goal
    printf("\nGoal G reached with cost 11\n");
    printf("Path: S -> A -> B -> B -> D -> G\n");

    return 0;
}
