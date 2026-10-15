/*
 * Check if a string is a palindrome using a STACK and a QUEUE.
 *
 * Push every character to the stack (LIFO) and enqueue it to the
 * queue (FIFO). Popping the stack reads the string backwards, while
 * dequeuing reads it forwards. If they match all the way, it is a
 * palindrome.
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int Data;
    struct node* Next;
};

typedef struct node* Stack;

/* A queue needs pointers to both ends. */
struct queueRecord {
    struct node* Front;
    struct node* Rear;
};

typedef struct queueRecord* Queue;

/* ---------- stack ---------- */

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

/* ---------- queue ---------- */

Queue CreateQueue(void) {
    Queue Q = (Queue)malloc(sizeof(struct queueRecord));
    Q->Front = Q->Rear = NULL;
    return Q;
}

int IsEmptyQueue(Queue Q) { return Q->Front == NULL; }

void Enqueue(int X, Queue Q) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->Data = X;
    temp->Next = NULL;
    if (Q->Rear == NULL)
        Q->Front = temp;
    else
        Q->Rear->Next = temp;
    Q->Rear = temp;
}

int Front(Queue Q) { return Q->Front->Data; }

void Dequeue(Queue Q) {
    if (IsEmptyQueue(Q))
        return;
    struct node* first = Q->Front;
    Q->Front = first->Next;
    if (Q->Front == NULL)
        Q->Rear = NULL;
    free(first);
}

void DisposeQueue(Queue Q) {
    while (!IsEmptyQueue(Q))
        Dequeue(Q);
    free(Q);
}

/* ---------- solution ---------- */

int isPalindrome(char str[]) {
    Stack S = CreateStack();
    Queue Q = CreateQueue();
    int i = 0;
    int result = 1;

    while (str[i] != '\0') {
        Push(str[i], S);
        Enqueue(str[i], Q);
        i++;
    }

    while (!IsEmpty(S) && !IsEmptyQueue(Q)) {
        if (Top(S) != Front(Q)) {
            result = 0;
            break;
        }
        Pop(S);
        Dequeue(Q);
    }

    /* free memory before returning (the original returned early and leaked) */
    DisposeStack(S);
    DisposeQueue(Q);
    return result;
}

int main(void) {
    char* words[] = {"racecar", "level", "hello", "a", ""};

    for (int k = 0; k < 5; k++)
        printf("\"%s\" -> %s\n", words[k], isPalindrome(words[k]) ? "palindrome" : "not palindrome");

    return 0;
}
