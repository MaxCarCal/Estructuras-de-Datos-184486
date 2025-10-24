#include <stdio.h>
#include <stdlib.h>

#define V 4 

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct Graph {
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }
    
    return graph;
}

void addDirectedEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
  
}


void printGraph(struct Graph* graph) {
    char vertices[V] = {'A', 'B', 'C', 'D'};
    
    printf("Adjacency List for Directed Graph:\n");
    printf("Vertex -> Adjacent Vertices (outgoing edges)\n");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < V; i++) {
        printf("%c -> ", vertices[i]);
        
        struct AdjListNode* current = graph->array[i].head;
        while (current != NULL) {
            printf("%c ", vertices[current->dest]);
            current = current->next;
            if (current != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }
}


void freeGraph(struct Graph* graph) {
    for (int i = 0; i < V; i++) {
        struct AdjListNode* current = graph->array[i].head;
        while (current != NULL) {
            struct AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

int main() {
   
    struct Graph* graph = createGraph();
    
    
    addDirectedEdge(graph, 0, 1);  // A → B
    addDirectedEdge(graph, 0, 2);  // A → C
    addDirectedEdge(graph, 1, 3);  // B → D
    addDirectedEdge(graph, 2, 1);  // C → B
    addDirectedEdge(graph, 3, 0);  // D → A
    
    printGraph(graph);
    
    printf("\nDetailed Edge Information:\n");
    printf("A → B: Edge from A to B\n");
    printf("A → C: Edge from A to C\n");
    printf("B → D: Edge from B to D\n");
    printf("C → B: Edge from C to B\n");
    printf("D → A: Edge from D to A\n");
    
    freeGraph(graph);
    
    return 0;
}


