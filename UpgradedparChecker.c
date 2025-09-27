#include <stdio.h>
#define MAX 1000

int isEmpty(int top) {
    return top == -1;
}

int isFull(int top, int cap) {
    return top == cap - 1;
}

int main(void) {
    char s[MAX];
    if (!fgets(s, sizeof s, stdin))
        return 0;
    
    char st[MAX];  // Stack for opening brackets
    int idx_stack[MAX];  // Stack for indices of opening brackets
    int top = -1;
    
    for (int i = 0; s[i] && s[i] != '\n'; ++i) {
        char c = s[i];
        
        // Ignore non-bracket characters
        if (c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}')
            continue;
            
        if (c == '(' || c == '[' || c == '{') {
            // Opening bracket - push to stack
            if (isFull(top, MAX)) {
                printf("%dERROR Stack full error\n", i);  // Stack full error
                return 0;
            }
            st[++top] = c;
            idx_stack[top] = i;
        } else {
            // Closing bracket
            if (isEmpty(top)) {
                printf("%dERROR // Closing bracket with empty stack\n", i);  // Closing bracket with empty stack
                return 0;
            }
            
            char t = st[top];
            int open_idx = idx_stack[top];
            top--;
            
            if ((c == ')' && t != '(') || 
                (c == ']' && t != '[') || 
                (c == '}' && t != '{')) {
                printf("%dERROR // Mismatched pair\n", i);  // Mismatched pair
                return 0;
            }
        }
    }
    
    if (!isEmpty(top)) {
        printf("%d ERROR First unmatched opener\n", idx_stack[0]);  // First unmatched opener
        return 0;
    }
    
    printf("BALANCED\n");
    return 0;
}


3 TESTS


Test 1: Balanced brackets
Input: ([]{})
Expected Output: OK


Test 2: Mismatched brackets
Input: ([)]
Expected Output: ERROR 2

Test 3: Closing bracket with empty stack
Input: ])
Expected Output: ERROR 0
