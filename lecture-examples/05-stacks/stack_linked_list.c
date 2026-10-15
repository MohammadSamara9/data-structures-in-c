/*
 * Lecture 5 - Stacks
 * Stack implemented with a linked list (header node).
 * Push and Pop work on the FIRST node after the header, so both are O(1).
 *
 * Fixed from the slides:
 *  - CreateStack: "(struct node)malloc(...)" casts to a struct, it must be a
 *    pointer cast "(Stack)malloc(...)". Also return NULL if malloc fails.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node* PtrToNode;
typedef PtrToNode Stack;

struct node {
    int Element;
    PtrToNode Next;
};

int IsEmpty(Stack S) {
    return S->Next == NULL;
}

void Pop(Stack S) {
    PtrToNode firstCell;
    if (IsEmpty(S))
        printf("Empty stack\n");
    else {
        firstCell = S->Next;
        S->Next = S->Next->Next;
        free(firstCell);
    }
}

void MakeEmpty(Stack S) {
    if (S == NULL)
        printf("Out of space!\n");
    else
        while (!IsEmpty(S))
            Pop(S);
}

Stack CreateStack(void) {
    Stack S;
    S = (Stack)malloc(sizeof(struct node));
    if (S == NULL) {
        printf("Out of space!\n");
        return NULL;
    }
    S->Next = NULL;
    MakeEmpty(S);
    return S;
}

int Top(Stack S) {
    if (!IsEmpty(S))
        return S->Next->Element;
    printf("Empty stack\n");
    return 0;
}

void Push(int X, Stack S) {
    PtrToNode temp;
    temp = (Stack)malloc(sizeof(struct node));
    if (temp == NULL)
        printf("Out of space!\n");
    else {
        temp->Element = X;
        temp->Next = S->Next;
        S->Next = temp;
    }
}

void DisposeStack(Stack S) {
    MakeEmpty(S);
    free(S);
}

int main(void) {
    Stack S = CreateStack();

    for (int i = 1; i <= 5; i++) {
        Push(i * 10, S);
        printf("Push %d\n", i * 10);
    }

    printf("Pop order (LIFO): ");
    while (!IsEmpty(S)) {
        printf("%d ", Top(S)); /* 50 40 30 20 10 */
        Pop(S);
    }
    printf("\n");

    DisposeStack(S);
    return 0;
}
