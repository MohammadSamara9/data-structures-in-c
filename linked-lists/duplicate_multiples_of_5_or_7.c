/*
 * (Recursion) Duplicate every node whose value is a multiple of 5 or 7.
 *
 * Example: 3 -> 5 -> 8 -> 14  becomes  3 -> 5 -> 5 -> 8 -> 14 -> 14
 *
 * After inserting the copy, we continue from the node AFTER the copy,
 * so the copy itself is not duplicated again.
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int Data;
    struct node* Next;
};

void create_duplicate(struct node* L) {
    if (L == NULL)
        return;

    if (L->Data % 5 == 0 || L->Data % 7 == 0) {
        struct node* temp = (struct node*)malloc(sizeof(struct node));

        temp->Data = L->Data;
        temp->Next = L->Next;
        L->Next = temp;

        create_duplicate(temp->Next);
    } else {
        create_duplicate(L->Next);
    }
}

/* ---------- helpers for the demo ---------- */

struct node* newNode(int data, struct node* next) {
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->Data = data;
    n->Next = next;
    return n;
}

void printList(struct node* L) {
    for (; L != NULL; L = L->Next)
        printf("%d ", L->Data);
    printf("\n");
}

void freeList(struct node* L) {
    while (L != NULL) {
        struct node* next = L->Next;
        free(L);
        L = next;
    }
}

int main(void) {
    struct node* L = newNode(3, newNode(5, newNode(8, newNode(14, NULL))));

    printf("Before: ");
    printList(L);
    create_duplicate(L);
    printf("After:  ");
    printList(L); /* 3 5 5 8 14 14 */

    freeList(L);
    return 0;
}
