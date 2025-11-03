#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new tree node
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Pre-order traversal: Root -> Left -> Right
void preOrderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);  // Visit root
    preOrderTraversal(root->left);  // Traverse left subtree
    preOrderTraversal(root->right); // Traverse right subtree
}

// In-order traversal: Left -> Root -> Right
void inOrderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left);  // Traverse left subtree
    printf("%d ", root->data);     // Visit root
    inOrderTraversal(root->right); // Traverse right subtree
}

// Post-order traversal: Left -> Right -> Root
void postOrderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    postOrderTraversal(root->left);  // Traverse left subtree
    postOrderTraversal(root->right); // Traverse right subtree
    printf("%d ", root->data);       // Visit root
}

int main() {
    // Create a binary tree with at least 5 nodes
    // Tree structure:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    
    printf("Binary Tree Created with 5 nodes:\n");
    printf("Tree Structure:\n");
    printf("       1\n");
    printf("      / \\\n");
    printf("     2   3\n");
    printf("    / \\\n");
    printf("   4   5\n\n");
    
    // Perform and print pre-order traversal
    printf("Pre-order traversal: ");
    preOrderTraversal(root);
    printf("\n");
    
    // Perform and print in-order traversal
    printf("In-order traversal:  ");
    inOrderTraversal(root);
    printf("\n");
    
    // Perform and print post-order traversal
    printf("Post-order traversal: ");
    postOrderTraversal(root);
    printf("\n");
    
    // Free the allocated memory (optional but good practice)
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);
    
    return 0;
}
