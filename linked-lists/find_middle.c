/*
 * Find the middle node of a singly linked list.
 *
 * Idea: two pointers. "slow" moves 1 step, "fast" moves 2 steps.
 * When fast reaches the end, slow is in the middle.
 * For an even length, it returns the second of the two middle nodes.
 *
 * Time: O(n)   Space: O(1)
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int Data;
    struct node* Next;
};

struct node* findMiddle(struct node* L1) {
    struct node* ptr = L1;
    struct node* fastPtr = L1;

    if (L1 == NULL)
        return NULL;

    while (fastPtr != NULL && fastPtr->Next != NULL) {
        ptr = ptr->Next;
        fastPtr = fastPtr->Next->Next;
    }

    return ptr;
}

/* ---------- helpers for the demo ---------- */

struct node* newNode(int data, struct node* next) {
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->Data = data;
    n->Next = next;
    return n;
}

void freeList(struct node* L) {
    while (L != NULL) {
        struct node* next = L->Next;
        free(L);
        L = next;
    }
}

int main(void) {
    /* 1 -> 2 -> 3 -> 4 -> 5 */
    struct node* L = newNode(1, newNode(2, newNode(3, newNode(4, newNode(5, NULL)))));

    printf("List: 1 -> 2 -> 3 -> 4 -> 5\n");
    printf("Middle: %d\n", findMiddle(L)->Data); /* 3 */

    freeList(L);
    return 0;
}
