#include <stdio.h>
#include <stdbool.h>

#define QUEUE_SIZE 5

int queue[QUEUE_SIZE];
int front = -1, rear = -1;

bool isFull() {
    return (rear + 1) % QUEUE_SIZE == front;
}

bool isEmpty() {
    return front == -1;
}

void enqueue(int value) {
    if (isFull()) {
        printf("Queue is full! Cannot enqueue %d\n", value);
        return;
    }
    
    if (isEmpty()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % QUEUE_SIZE;
    }
    
    queue[rear] = value;
    printf("Enqueued: %d\n", value);
}

int dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! Cannot dequeue\n");
        return -1;
    }
    
    int value = queue[front];
    
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % QUEUE_SIZE;
    }
    
    return value;
}

void printQueue() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    
    printf("Queue: ");
    
    if (rear < front) {
        // Print from front to end, then from start to rear
        for (int i = front; i < QUEUE_SIZE; i++)
            printf("%d ", queue[i]);
        for (int i = 0; i <= rear; i++)
            printf("%d ", queue[i]);
    } else {
        // Print from front to rear
        for (int i = front; i <= rear; i++)
            printf("%d ", queue[i]);
    }
    printf("\n");
}

int main() {
    int choice, value;
    
    printf("Circular Queue Implementation (Size: %d)\n", QUEUE_SIZE);
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. Exit\n");
    
    while (1) {
        printf("\nEnter your choice (1-3): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (isFull()) {
                    printf("Queue is full! Cannot enqueue.\n");
                } else {
                    printf("Enter value to enqueue: ");
                    scanf("%d", &value);
                    enqueue(value);
                }
                printQueue();
                break;
                
            case 2:
                if (!isEmpty()) {
                    value = dequeue();
                    printf("Dequeued: %d\n", value);
                }
                printQueue();
                break;
                
            case 3:
                printf("Exit program.\n");
                return 0;
                
            default:
                printf("Error, Please enter 1, 2, or 3.\n");
        }
    }
    
    return 0;
}
