#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define INF 9999

typedef struct {
    char node;
    int cost;
} Item;

typedef struct {
    Item items[MAX];
    int size;
} Binding;

// History and path
char history[MAX];
int historySize = 0;
char path[MAX];
int pathSize = 0;

// Oracle cost
int ORACLE = 11;
int printedBindings[MAX] = {0}; // Track printed bindings

int inHistory(char node) {
    for (int i = 0; i < historySize; i++)
        if (history[i] == node) return 1;
    return 0;
}

void addHistory(char node) {
    history[historySize++] = node;
}

void printBinding(Binding *b, int num) {
    printf("Binding B%d: ", num);
    for (int i = 0; i < b->size; i++)
        printf("%c(g=%d) ", b->items[i].node, b->items[i].cost);
    printf("\n");
}

int dfs(Binding B[], int numBindings, char current, int cost) {
    path[pathSize++] = current;
    addHistory(current);

    if (current == 'G' && cost <= ORACLE) {
        printf("\nGoal reached: ");
        for (int i = 0; i < pathSize; i++)
            printf("%c ", path[i]);
        printf("\nCost = %d\n", cost);
        return 1;
    }

    for (int b = 0; b < numBindings; b++) {
        int containsCurrent = 0;
        for (int i = 0; i < B[b].size; i++)
            if (B[b].items[i].node == current) containsCurrent = 1;

        if (!containsCurrent) continue;

        // Print binding only once
        if (!printedBindings[b]) {
            printBinding(&B[b], b+1);
            printedBindings[b] = 1;
        }

        for (int i = 0; i < B[b].size; i++) {
            Item it = B[b].items[i];
            if (it.node == current) continue;
            if (!inHistory(it.node) && (cost + it.cost - B[b].items[0].cost) <= ORACLE)
                if (dfs(B, numBindings, it.node, cost + it.cost - B[b].items[0].cost))
                    return 1;
        }
    }

    pathSize--; // backtrack
    return 0;
}

int main() {
    Binding B[4];

    B[0].size = 2; B[0].items[0] = (Item){'S',0}; B[0].items[1] = (Item){'A',3};
    B[1].size = 2; B[1].items[0] = (Item){'A',3}; B[1].items[1] = (Item){'B',6};
    B[2].size = 2; B[2].items[0] = (Item){'B',6}; B[2].items[1] = (Item){'D',11};
    B[3].size = 2; B[3].items[0] = (Item){'D',11}; B[3].items[1] = (Item){'G',11};

    printf("Oracle Cost = %d\n", ORACLE);

    if (!dfs(B, 4, 'S', 0))
        printf("\nGoal not found within oracle cost.\n");

    return 0;
}
