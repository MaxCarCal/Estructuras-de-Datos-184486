#include <stdio.h>
#include <stdlib.h>

#define V 4

// Function to initialize adjacency matrix with zeros
void initializeMatrix(int matrix[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Function to add an edge to the adjacency matrix
void addEdge(int matrix[V][V], int vertex1, int vertex2) {
    matrix[vertex1][vertex2] = 1;
    matrix[vertex2][vertex1] = 1;  // Undirected graph
}

// Function to print the adjacency matrix
void printMatrix(int matrix[V][V]) {
    char vertices[V] = {'A', 'B', 'C', 'D'};
    
    // Print header
    printf("   ");
    for (int i = 0; i < V; i++) {
        printf("%c ", vertices[i]);
    }
    printf("\n");
    
    // Print matrix with row labels
    for (int i = 0; i < V; i++) {
        printf("%c: ", vertices[i]);
        for (int j = 0; j < V; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int adjacencyMatrix[V][V];
    
    // Initialize matrix with zeros
    initializeMatrix(adjacencyMatrix);
    
    // Map vertices to indices: A=0, B=1, C=2, D=3
    // Add edges: {A,B}, {A,C}, {B,D}
    addEdge(adjacencyMatrix, 0, 1);  // A-B
    addEdge(adjacencyMatrix, 0, 2);  // A-C
    addEdge(adjacencyMatrix, 1, 3);  // B-D
    
    // Print the adjacency matrix
    printf("Adjacency Matrix for the Undirected Graph:\n");
    printf("Vertices: A, B, C, D\n");
    printf("Edges: {A,B}, {A,C}, {B,D}\n\n");
    
    printMatrix(adjacencyMatrix);
    
    return 0;
}
