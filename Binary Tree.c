#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

int heap[MAX_SIZE];
int heapSize = 0;

// Function prototypes
void insert(int item);
int removeMax(void);
void reHeapDown(int i);
void showHeap(void);
void printHeapWithChildren(void);
void swap(int *a, int *b);

int main() {
    int choice, value, k, i;
    
    printf("Max-Heap Implementation\n");
    printf("=======================\n");
    
    while(1) {
        printf("\nMenu:\n");
        printf("1. Insert elements\n");
        printf("2. Remove max element K times\n");
        printf("3. Show heap\n");
        printf("4. Print heap with children\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter the number of elements to insert: ");
                scanf("%d", &k);
                printf("Enter %d integers:\n", k);
                for(i = 0; i < k; i++) {
                    scanf("%d", &value);
                    insert(value);
                    printf("After inserting %d:\n", value);
                    showHeap();
                }
                break;
                
            case 2:
                if(heapSize == 0) {
                    printf("Heap is empty!\n");
                    break;
                }
                printf("Enter K (number of times to remove max): ");
                scanf("%d", &k);
                if(k > heapSize) k = heapSize;
                
                for(i = 0; i < k; i++) {
                    int maxVal = removeMax();
                    printf("Removed max element: %d\n", maxVal);
                    printf("Heap after removal:\n");
                    showHeap();
                }
                break;
                
            case 3:
                showHeap();
                break;
                
            case 4:
                printHeapWithChildren();
                break;
                
            case 5:
                printf("Exiting program.\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

// Swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Insert an element into the max-heap
void insert(int item) {
    if(heapSize >= MAX_SIZE) {
        printf("Heap is full! Cannot insert %d\n", item);
        return;
    }
    
    // Add new element at the end
    heap[heapSize] = item;
    int current = heapSize;
    heapSize++;
    
    // Reheap upward (bubble up)
    while(current > 0 && heap[current] > heap[(current - 1) / 2]) {
        swap(&heap[current], &heap[(current - 1) / 2]);
        current = (current - 1) / 2;
    }
}

// Remove and return the maximum element (root)
int removeMax(void) {
    if(heapSize <= 0) {
        printf("Heap is empty!\n");
        return INT_MIN;
    }
    
    if(heapSize == 1) {
        heapSize--;
        return heap[0];
    }
    
    // Store the max value (root)
    int maxVal = heap[0];
    
    // Move last element to root
    heap[0] = heap[heapSize - 1];
    heapSize--;
    
    // Reheap downward from root
    reHeapDown(0);
    
    return maxVal;
}

// Reheap downward starting from index i
void reHeapDown(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    // Check if left child exists and is greater than current largest
    if(left < heapSize && heap[left] > heap[largest]) {
        largest = left;
    }
    
    // Check if right child exists and is greater than current largest
    if(right < heapSize && heap[right] > heap[largest]) {
        largest = right;
    }
    
    // If largest is not the current node, swap and continue reheaping
    if(largest != i) {
        swap(&heap[i], &heap[largest]);
        reHeapDown(largest);
    }
}

// Display the heap as an array
void showHeap(void) {
    if(heapSize == 0) {
        printf("Heap is empty!\n");
        return;
    }
    
    printf("Heap (array representation): [");
    for(int i = 0; i < heapSize; i++) {
        printf("%d", heap[i]);
        if(i < heapSize - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    
    // Also show tree-like structure
    printf("Tree visualization:\n");
    int level = 0;
    int levelSize = 1;
    int count = 0;
    
    for(int i = 0; i < heapSize; i++) {
        printf("%d ", heap[i]);
        count++;
        
        if(count == levelSize) {
            printf("\n");
            level++;
            levelSize = 1 << level; // 2^level
            count = 0;
        }
    }
    if(count > 0) printf("\n");
}

// Print each node with its left and right children
void printHeapWithChildren(void) {
    if(heapSize == 0) {
        printf("Heap is empty!\n");
        return;
    }
    
    printf("\nHeap Structure (Node [index] = value -> Left Child | Right Child):\n");
    printf("===================================================================\n");
    
    for(int i = 0; i < heapSize; i++) {
        int leftChild = (2 * i + 1) < heapSize ? heap[2 * i + 1] : -1;
        int rightChild = (2 * i + 2) < heapSize ? heap[2 * i + 2] : -1;
        
        printf("Node [%d] = %d", i, heap[i]);
        
        if(leftChild != -1 || rightChild != -1) {
            printf(" -> ");
            if(leftChild != -1) {
                printf("Left[%d]=%d", 2*i+1, leftChild);
            } else {
                printf("Left[%d]=NULL", 2*i+1);
            }
            
            printf(" | ");
            
            if(rightChild != -1) {
                printf("Right[%d]=%d", 2*i+2, rightChild);
            } else {
                printf("Right[%d]=NULL", 2*i+2);
            }
        } else {
            printf(" -> Leaf node");
        }
        printf("\n");
    }
    
    // Print parent-child relationships
    printf("\nParent-Child Relationships:\n");
    for(int i = 0; i < heapSize; i++) {
        int parentIndex = (i - 1) / 2;
        if(i == 0) {
            printf("Root node [0] = %d (no parent)\n", heap[i]);
        } else {
            printf("Node [%d] = %d (Parent [%d] = %d)\n", 
                   i, heap[i], parentIndex, heap[parentIndex]);
        }
    }
}
