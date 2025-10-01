#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

Queue* createQueue();
bool isEmpty(Queue* q);
void enqueue(Queue* q, int data);
int dequeue(Queue* q);
int peek(Queue* q);
int getSize(Queue* q);
void displayQueue(Queue* q);
void freeQueue(Queue* q);
Node* createNode(int data);

int main() {
    Queue* queue = createQueue();
    int choice, data;
    
    do {
        printf("\n1. Add number to queue\n");
        printf("2. Remove number from queue\n");
        printf("3. See first number in queue\n");
        printf("4. Check if queue is empty\n");
        printf("5. See how many numbers in queue\n");
        printf("6. Show all numbers in queue\n");
        printf("7. Exit\n");
        printf("What do you want to do? ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter number to add: ");
                scanf("%d", &data);
                enqueue(queue, data);
                break;
                
            case 2:
                if (!isEmpty(queue)) {
                    data = dequeue(queue);
                    printf("Removed: %d\n", data);
                } else {
                    printf("Queue is empty!\n");
                }
                break;
                
            case 3:
                if (!isEmpty(queue)) {
                    data = peek(queue);
                    printf("First number is: %d\n", data);
                } else {
                    printf("Queue is empty!\n");
                }
                break;
                
            case 4:
                if (isEmpty(queue)) {
                    printf("Yes, queue is empty\n");
                } else {
                    printf("No, queue has numbers\n");
                }
                break;
                
            case 5:
                printf("Numbers in queue: %d\n", getSize(queue));
                break;
                
            case 6:
                displayQueue(queue);
                break;
                
            case 7:
                printf("Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 7);
    
    freeQueue(queue);
    
    return 0;
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q != NULL) {
        q->front = NULL;
        q->rear = NULL;
        q->size = 0;
    }
    return q;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

bool isEmpty(Queue* q) {
    return (q->front == NULL);
}

void enqueue(Queue* q, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        printf("Error adding number!\n");
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
    printf("Added: %d\n", data);
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }
    
    Node* temp = q->front;
    int data = temp->data;
    
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    q->size--;
    
    return data;
}

int peek(Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }
    
    return q->front->data;
}

int getSize(Queue* q) {
    return q->size;
}

void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    
    printf("Queue: ");
    Node* current = q->front;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

void freeQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    free(q);
}
