#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* head = NULL;

// Function prototypes
Node* createNode(int data);
void displayNodes();
void insertAtBeginning(int data);
void insertAtPosition(int data, int position);
void insertAtEnd(int data);
void deleteAtBeginning();
void deleteAtEnd();
void deleteAtPosition(int position);

int main() {
    int choice, data, position;
    
    printf("Singly Linked List Operations\n");
    
    do {
        printf("\nMenu:\n");
        printf("1. Display List\n");
        printf("2. Insert at Beginning\n");
        printf("3. Insert at Specific Position\n");
        printf("4. Insert at End\n");
        printf("5. Delete at Beginning\n");
        printf("6. Delete at End\n");
        printf("7. Delete at Specific Position\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                displayNodes();
                break;
            case 2:
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                insertAtBeginning(data);
                break;
            case 3:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtPosition(data, position);
                break;
            case 4:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(data);
                break;
            case 5:
                deleteAtBeginning();
                break;
            case 6:
                deleteAtEnd();
                break;
            case 7:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteAtPosition(position);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 8);
    
    // Free all memory before exiting
    Node* current = head;
    while(current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}

// a. Create Node
/*
Algorithm:
1. Allocate memory for new node
2. If allocation successful:
   - Set node data to input value
   - Set next pointer to NULL
3. Return pointer to new node

Input: integer data
Output: Pointer to newly created node, or NULL if memory allocation fails
*/
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

// b. Display Nodes
/*
Algorithm:
1. If list is empty, display appropriate message
2. Else:
   - Start from head node
   - Traverse through each node until NULL
   - Print data of each node

Input: None
Output: Prints the entire list or "List is empty" message
*/
void displayNodes() {
    if(head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* current = head;
    printf("List: ");
    while(current != NULL) {
        printf("%d", current->data);
        if(current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}

// c. Insert Node at beginning
/*
Algorithm:
1. Create new node with given data
2. If memory allocation fails, return error
3. Set new node's next to current head
4. Update head to point to new node

Input: integer data
Output: None (modifies the list)
*/
void insertAtBeginning(int data) {
    Node* newNode = createNode(data);
    if(newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    newNode->next = head;
    head = newNode;
    printf("Node with data %d inserted at beginning.\n", data);
}

// d. Insert Node in specific position
/*
Algorithm:
1. If position is 1, insert at beginning
2. Else:
   - Traverse to (position-1)th node
   - If position is invalid, display error
   - Create new node
   - Insert between current and current->next

Input: integer data, integer position (1-based indexing)
Output: None (modifies the list)
*/
void insertAtPosition(int data, int position) {
    if(position < 1) {
        printf("Invalid position! Position must be >= 1.\n");
        return;
    }
    
    if(position == 1) {
        insertAtBeginning(data);
        return;
    }
    
    Node* newNode = createNode(data);
    if(newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    Node* current = head;
    int count = 1;
    
    // Traverse to (position-1)th node
    while(current != NULL && count < position - 1) {
        current = current->next;
        count++;
    }
    
    if(current == NULL) {
        printf("Position %d is out of bounds! List has only %d nodes.\n", position, count);
        free(newNode);
        return;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    printf("Node with data %d inserted at position %d.\n", data, position);
}

// e. Insert Node at the end of Linked List
/*
Algorithm:
1. Create new node
2. If list is empty, set new node as head
3. Else:
   - Traverse to last node
   - Set last node's next to new node

Input: integer data
Output: None (modifies the list)
*/
void insertAtEnd(int data) {
    Node* newNode = createNode(data);
    if(newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    if(head == NULL) {
        head = newNode;
    } else {
        Node* current = head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    printf("Node with data %d inserted at end.\n", data);
}

// f. Delete Node at beginning
/*
Algorithm:
1. If list is empty, display error
2. Else:
   - Store head in temporary pointer
   - Move head to next node
   - Free the old head node

Input: None
Output: None (modifies the list)
*/
void deleteAtBeginning() {
    if(head == NULL) {
        printf("List is empty! Cannot delete from beginning.\n");
        return;
    }
    
    Node* temp = head;
    head = head->next;
    printf("Node with data %d deleted from beginning.\n", temp->data);
    free(temp);
}

// g. Delete Node at end
/*
Algorithm:
1. If list is empty, display error
2. If only one node, delete it and set head to NULL
3. Else:
   - Traverse to second last node
   - Free the last node
   - Set second last node's next to NULL

Input: None
Output: None (modifies the list)
*/
void deleteAtEnd() {
    if(head == NULL) {
        printf("List is empty! Cannot delete from end.\n");
        return;
    }
    
    if(head->next == NULL) {
        // Only one node in list
        printf("Node with data %d deleted from end.\n", head->data);
        free(head);
        head = NULL;
        return;
    }
    
    Node* current = head;
    // Traverse to second last node
    while(current->next->next != NULL) {
        current = current->next;
    }
    
    printf("Node with data %d deleted from end.\n", current->next->data);
    free(current->next);
    current->next = NULL;
}

// h. Delete Node at position
/*
Algorithm:
1. If position is 1, delete from beginning
2. Else:
   - Traverse to (position-1)th node
   - If position is invalid, display error
   - Store node to delete in temporary pointer
   - Link previous node to next node
   - Free the node

Input: integer position (1-based indexing)
Output: None (modifies the list)
*/
void deleteAtPosition(int position) {
    if(head == NULL) {
        printf("List is empty! Cannot delete from position %d.\n", position);
        return;
    }
    
    if(position < 1) {
        printf("Invalid position! Position must be >= 1.\n");
        return;
    }
    
    if(position == 1) {
        deleteAtBeginning();
        return;
    }
    
    Node* current = head;
    int count = 1;
    
    // Traverse to (position-1)th node
    while(current != NULL && count < position - 1) {
        current = current->next;
        count++;
    }
    
    if(current == NULL || current->next == NULL) {
        printf("Position %d is out of bounds! List has only %d nodes.\n", position, count);
        return;
    }
    
    Node* temp = current->next;
    current->next = temp->next;
    printf("Node with data %d deleted from position %d.\n", temp->data, position);
    free(temp);
}
