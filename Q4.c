#include <stdio.h>
#include <stdlib.h>

void push(int stack[], int *top, int maxSize);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main() {
    int maxSize;
    printf("Enter maximum size of stack: ");
    if (scanf("%d", &maxSize) != 1 || maxSize <= 0) { printf("Invalid size.\n"); return 0; }
    int *stack = malloc(sizeof(int) * maxSize);
    if (!stack) { printf("Memory allocation failed.\n"); return 0; }
    int top = -1;
    int choice;

    while (1) {
        printf("\n--- Stack Menu ---\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Choose: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: push(stack, &top, maxSize); break;
            case 2: pop(stack, &top); break;
            case 3: peek(stack, top); break;
            case 4: display(stack, top); break;
            case 5: free(stack); printf("Exiting...\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }
    free(stack);
    return 0;
}

void push(int stack[], int *top, int maxSize) {
    if (*top >= maxSize - 1) {
        printf("Stack Overflow! Cannot push.\n");
        return;
    }
    int value;
    printf("Enter value to push: ");
    if (scanf("%d", &value) != 1) { printf("Invalid input.\n"); return; }
    (*top)++;
    stack[*top] = value;
    printf("%d pushed to stack.\n", value);
}

void pop(int stack[], int *top) {
    if (*top < 0) {
        printf("Stack Underflow! No elements to pop.\n");
        return;
    }
    int val = stack[*top];
    (*top)--;
    printf("Popped: %d\n", val);
}

void peek(int stack[], int top) {
    if (top < 0) {
        printf("Stack is empty.\n");
    } else {
        printf("Top element: %d\n", stack[top]);
    }
}

void display(int stack[], int top) {
    if (top < 0) { printf("Stack is empty.\n"); return; }
    printf("Stack elements (top to bottom):\n");
    for (int i = top; i >= 0; i--) printf("%d\n", stack[i]);
}
