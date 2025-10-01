#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Circular Linked List structure
typedef struct {
    Node* head;
    Node* tail;
    int size;
} CircularLinkedList;

// Function prototypes
CircularLinkedList* createList();
void addToFront(CircularLinkedList* list, int data);
void addToEnd(CircularLinkedList* list, int data);
void addAtPosition(CircularLinkedList* list, int data, int position);
int removeFromFront(CircularLinkedList* list);
int removeFromEnd(CircularLinkedList* list);
int removeFromPosition(CircularLinkedList* list, int position);
int search(CircularLinkedList* list, int data);
void traverse(CircularLinkedList* list);
int size(CircularLinkedList* list);
bool isEmpty(CircularLinkedList* list);
void clear(CircularLinkedList* list);
void display(CircularLinkedList* list);
Node* getHead(CircularLinkedList* list);
Node* getTail(CircularLinkedList* list);
void freeList(CircularLinkedList* list);

// Create a new circular linked list
CircularLinkedList* createList() {
    CircularLinkedList* list = (CircularLinkedList*)malloc(sizeof(CircularLinkedList));
    if (list == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Add to the front of the list
void addToFront(CircularLinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = data;
    
    if (isEmpty(list)) {
        newNode->next = newNode;
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
        list->tail->next = newNode;
    }
    list->size++;
}

// Add to the end of the list
void addToEnd(CircularLinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = data;
    
    if (isEmpty(list)) {
        newNode->next = newNode;
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

// Add at specific position (0-based indexing)
void addAtPosition(CircularLinkedList* list, int data, int position) {
    if (position < 0 || position > list->size) {
        printf("Invalid position! Position should be between 0 and %d\n", list->size);
        return;
    }
    
    if (position == 0) {
        addToFront(list, data);
    } else if (position == list->size) {
        addToEnd(list, data);
    } else {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }
        newNode->data = data;
        
        Node* current = list->head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        list->size++;
    }
}

// Remove from front of the list
int removeFromFront(CircularLinkedList* list) {
    if (isEmpty(list)) {
        printf("List is empty! Cannot remove from front.\n");
        return -1;
    }
    
    Node* temp = list->head;
    int data = temp->data;
    
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->tail->next = list->head;
    }
    
    free(temp);
    list->size--;
    return data;
}

// Remove from end of the list
int removeFromEnd(CircularLinkedList* list) {
    if (isEmpty(list)) {
        printf("List is empty! Cannot remove from end.\n");
        return -1;
    }
    
    if (list->size == 1) {
        return removeFromFront(list);
    }
    
    Node* current = list->head;
    while (current->next != list->tail) {
        current = current->next;
    }
    
    Node* temp = list->tail;
    int data = temp->data;
    
    current->next = list->head;
    list->tail = current;
    
    free(temp);
    list->size--;
    return data;
}

// Remove from specific position (0-based indexing)
int removeFromPosition(CircularLinkedList* list, int position) {
    if (isEmpty(list)) {
        printf("List is empty! Cannot remove from position.\n");
        return -1;
    }
    
    if (position < 0 || position >= list->size) {
        printf("Invalid position! Position should be between 0 and %d\n", list->size - 1);
        return -1;
    }
    
    if (position == 0) {
        return removeFromFront(list);
    } else if (position == list->size - 1) {
        return removeFromEnd(list);
    } else {
        Node* current = list->head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        
        Node* temp = current->next;
        int data = temp->data;
        current->next = temp->next;
        
        free(temp);
        list->size--;
        return data;
    }
}

// Search for an element in the list
int search(CircularLinkedList* list, int data) {
    if (isEmpty(list)) {
        return -1;
    }
    
    Node* current = list->head;
    int position = 0;
    
    do {
        if (current->data == data) {
            return position;
        }
        current = current->next;
        position++;
    } while (current != list->head);
    
    return -1;
}

// Traverse and print all elements
void traverse(CircularLinkedList* list) {
    if (isEmpty(list)) {
        printf("List is empty!\n");
        return;
    }
    
    Node* current = list->head;
    printf("List elements: ");
    
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->head);
    
    printf("\n");
}

// Get the size of the list
int size(CircularLinkedList* list) {
    return list->size;
}

// Check if list is empty
bool isEmpty(CircularLinkedList* list) {
    return list->size == 0;
}

// Clear all elements from the list
void clear(CircularLinkedList* list) {
    while (!isEmpty(list)) {
        removeFromFront(list);
    }
}

// Display list information
void display(CircularLinkedList* list) {
    printf("Circular Linked List:\n");
    printf("Size: %d\n", list->size);
    printf("Empty: %s\n", isEmpty(list) ? "Yes" : "No");
    
    if (!isEmpty(list)) {
        printf("Head: %d\n", list->head->data);
        printf("Tail: %d\n", list->tail->data);
        printf("Tail->next points to head: %s\n", list->tail->next == list->head ? "Yes" : "No");
    }
    
    traverse(list);
    printf("\n");
}

// Get head node
Node* getHead(CircularLinkedList* list) {
    return list->head;
}

// Get tail node
Node* getTail(CircularLinkedList* list) {
    return list->tail;
}

// Free the entire list
void freeList(CircularLinkedList* list) {
    clear(list);
    free(list);
}

// Interactive menu for testing
void menu() {
    CircularLinkedList* list = createList();
    int choice, data, position, result;
    
    printf("=== Circular Linked List ADT Test Program ===\n");
    
    do {
        printf("\nMenu:\n");
        printf("1. Add to front\n");
        printf("2. Add to end\n");
        printf("3. Add at position\n");
        printf("4. Remove from front\n");
        printf("5. Remove from end\n");
        printf("6. Remove from position\n");
        printf("7. Search\n");
        printf("8. Traverse\n");
        printf("9. Display list info\n");
        printf("10. Clear list\n");
        printf("11. Get size\n");
        printf("12. Check if empty\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data to add to front: ");
                scanf("%d", &data);
                addToFront(list, data);
                break;
                
            case 2:
                printf("Enter data to add to end: ");
                scanf("%d", &data);
                addToEnd(list, data);
                break;
                
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position (0-%d): ", list->size);
                scanf("%d", &position);
                addAtPosition(list, data, position);
                break;
                
            case 4:
                result = removeFromFront(list);
                if (result != -1) {
                    printf("Removed from front: %d\n", result);
                }
                break;
                
            case 5:
                result = removeFromEnd(list);
                if (result != -1) {
                    printf("Removed from end: %d\n", result);
                }
                break;
                
            case 6:
                printf("Enter position to remove (0-%d): ", list->size - 1);
                scanf("%d", &position);
                result = removeFromPosition(list, position);
                if (result != -1) {
                    printf("Removed from position %d: %d\n", position, result);
                }
                break;
                
            case 7:
                printf("Enter data to search: ");
                scanf("%d", &data);
                result = search(list, data);
                if (result != -1) {
                    printf("Data %d found at position %d\n", data, result);
                } else {
                    printf("Data %d not found in the list\n", data);
                }
                break;
                
            case 8:
                traverse(list);
                break;
                
            case 9:
                display(list);
                break;
                
            case 10:
                clear(list);
                printf("List cleared!\n");
                break;
                
            case 11:
                printf("List size: %d\n", size(list));
                break;
                
            case 12:
                printf("List is %s\n", isEmpty(list) ? "empty" : "not empty");
                break;
                
            case 0:
                printf("Exiting program...\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
    
    freeList(list);
}

int main() {
    menu();
    return 0;
}
