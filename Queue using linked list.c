#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Queue Node Structure
typedef struct node {
    int data;
    struct node* next;
} Node;

// Queue Structure
typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

// Queue ADT Function Prototypes
Queue* createQueue();
bool isEmpty(Queue* q);
void enqueue(Queue* q, int data);
int dequeue(Queue* q);
int peek(Queue* q);
int getSize(Queue* q);
void displayQueue(Queue* q);
void freeQueue(Queue* q);

// Helper Functions
Node* createNode(int data);

int main() {
    Queue* queue = createQueue();
    int choice, data;
    
    printf("Queue ADT Implementation using Linked List\n");
    printf("==========================================\n");
    
    do {
        printf("\nQueue Operations Menu:\n");
        printf("1. Enqueue (Add to rear)\n");
        printf("2. Dequeue (Remove from front)\n");
        printf("3. Peek (View front element)\n");
        printf("4. Check if queue is empty\n");
        printf("5. Get queue size\n");
        printf("6. Display queue\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter data to enqueue: ");
                scanf("%d", &data);
                enqueue(queue, data);
                break;
                
            case 2:
                if (!isEmpty(queue)) {
                    data = dequeue(queue);
                    printf("Dequeued element: %d\n", data);
                } else {
                    printf("Queue is empty! Cannot dequeue.\n");
                }
                break;
                
            case 3:
                if (!isEmpty(queue)) {
                    data = peek(queue);
                    printf("Front element: %d\n", data);
                } else {
                    printf("Queue is empty! No front element.\n");
                }
                break;
                
            case 4:
                if (isEmpty(queue)) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Queue is not empty.\n");
                }
                break;
                
            case 5:
                printf("Queue size: %d\n", getSize(queue));
                break;
                
            case 6:
                displayQueue(queue);
                break;
                
            case 7:
                printf("Exiting program...\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 7);
    
    // Free memory before exiting
    freeQueue(queue);
    
    return 0;
}

// Queue ADT Implementation

/*
Function: createQueue
Algorithm:
1. Allocate memory for queue structure
2. Initialize front and rear pointers to NULL
3. Initialize size to 0
4. Return pointer to created queue

Input: None
Output: Pointer to newly created queue
*/
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q != NULL) {
        q->front = NULL;
        q->rear = NULL;
        q->size = 0;
    }
    return q;
}

/*
Function: isEmpty
Algorithm:
1. Check if front pointer is NULL
2. Return true if empty, false otherwise

Input: Queue pointer
Output: Boolean indicating if queue is empty
*/
bool isEmpty(Queue* q) {
    return (q->front == NULL);
}

/*
Function: enqueue
Algorithm:
1. Create new node with given data
2. If memory allocation fails, return error
3. If queue is empty:
   - Set both front and rear to new node
4. Else:
   - Add new node after current rear
   - Update rear to point to new node
5. Increment size counter

Input: Queue pointer, integer data
Output: None (modifies the queue)
*/
void enqueue(Queue* q, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot enqueue %d\n", data);
        return;
    }
    
    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
    printf("Enqueued: %d\n", data);
}

/*
Function: dequeue
Algorithm:
1.
