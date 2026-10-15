/*
 * Slice a stack: move the elements at positions [i, j) (counted from the
 * BOTTOM, starting at 0) into a new stack, and keep the rest in S in
 * their original order.
 *
 * Example: S (bottom -> top) = 10 20 30 40 50, i = 1, j = 3
 *          result = 20 30      S = 10 40 50
 *
 * Idea: pour S into a temp stack (this reverses it, so the bottom is now
 * on top), then pour it back while counting positions.
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int Data;
    struct node* Next;
};

typedef struct node* Stack;

/* ---------- stack (linked list with a header node) ---------- */

Stack CreateStack(void) {
    Stack S = (Stack)malloc(sizeof(struct node));
    S->Next = NULL;
    return S;
}

int IsEmpty(Stack S) { return S->Next == NULL; }

void Push(int X, Stack S) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->Data = X;
    temp->Next = S->Next;
    S->Next = temp;
}

int Top(Stack S) { return S->Next->Data; }

void Pop(Stack S) {
    if (IsEmpty(S))
        return;
    struct node* first = S->Next;
    S->Next = first->Next;
    free(first);
}

void DisposeStack(Stack S) {
    while (!IsEmpty(S))
        Pop(S);
    free(S);
}

/* ---------- solution ---------- */

Stack SliceStack(Stack S, int i, int j) {
    Stack temp = CreateStack();
    Stack result = CreateStack();
    int index = 0;
    int x;

    while (!IsEmpty(S)) {
        x = Top(S);
        Pop(S);
        Push(x, temp);
    }

    while (!IsEmpty(temp)) {
        x = Top(temp);
        Pop(temp);

        if (index >= i && index < j)
            Push(x, result);
        else
            Push(x, S);

        index++;
    }

    DisposeStack(temp); /* the original code forgot to free temp */
    return result;
}

/* ---------- demo ---------- */

/* Prints bottom -> top using recursion. */
void printBottomToTop(struct node* p) {
    if (p == NULL)
        return;
    printBottomToTop(p->Next);
    printf("%d ", p->Data);
}

int main(void) {
    Stack S = CreateStack();
    for (int v = 10; v <= 50; v += 10)
        Push(v, S);

    printf("S before: ");
    printBottomToTop(S->Next);
    printf("\n");

    Stack R = SliceStack(S, 1, 3);

    printf("Slice [1,3): ");
    printBottomToTop(R->Next); /* 20 30 */
    printf("\nS after:  ");
    printBottomToTop(S->Next); /* 10 40 50 */
    printf("\n");

    DisposeStack(S);
    DisposeStack(R);
    return 0;
}
