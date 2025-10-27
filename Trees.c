#include <stdio.h>

#define MAX_NODES 11  


char tree_nodes[MAX_NODES] = {'G', 'D', 'I', 'B', 'F', 'H', 'J', 'A', 'C', 'E', 'K'};


int left_child[MAX_NODES];
int right_child[MAX_NODES];

// Total number of elements
int tree_numElements = 11;

void build_full_binary_tree() {
    // Initialize all children to -1
    for (int i = 0; i < MAX_NODES; i++) {
        left_child[i] = -1;
        right_child[i] = -1;
    }

    // Root: G (0)
    left_child[0] = 1;   // D
    right_child[0] = 2;  // I

    // D (1)
    left_child[1] = 3;   // B
    right_child[1] = 4;  // F

    // I (2)
    left_child[2] = 5;   // H
    right_child[2] = 6;  // J

    // B (3)
    left_child[3] = 7;   // A
    right_child[3] = 8;  // C

    // F (4) — now has both children
    left_child[4] = 9;   // E
    right_child[4] = 10; // K (new node)

    // H (5), J (6), A (7), C (8), E (9), K (10): no children
}

void print_tree() {
    printf("Full Binary Tree (Index -> Label: Left, Right)\n");
    for (int i = 0; i < tree_numElements; i++) {
        printf("%2d -> %c: ", i, tree_nodes[i]);
        if (left_child[i] != -1)
            printf("L=%2d(%c) ", left_child[i], tree_nodes[left_child[i]]);
        else
            printf("L= -   ");
        if (right_child[i] != -1)
            printf("R=%2d(%c)", right_child[i], tree_nodes[right_child[i]]);
        else
            printf("R= -  ");
        printf("\n");
    }
    printf("\ntree_numElements = %d\n", tree_numElements);
}

int main() {
    build_full_binary_tree();
    print_tree();
    return 0;
}
