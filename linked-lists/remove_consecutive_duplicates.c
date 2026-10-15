/*
 * (Recursion) Remove consecutive duplicate values from a list.
 *
 * Example: 1 -> 1 -> 2 -> 3 -> 3 -> 3 -> 1  becomes  1 -> 2 -> 3 -> 1
 *
 * If the current node equals the next one, delete the next node and
 * check the SAME node again (there may be more duplicates).
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int Data;
    struct node* Next;
};

void removeConsecutiveDuplicates(struct node* L) {
    struct node* temp;

    if (L == NULL || L->Next == NULL)
        return;

    if (L->Data == L->Next->Data) {
        temp = L->Next;
        L->Next = temp->Next;
        free(temp);

        removeConsecutiveDuplicates(L);
    } else {
        removeConsecutiveDuplicates(L->Next);
    }
}

/* ---------- helpers for the demo ---------- */

struct node* fromArray(const int a[], int n) {
    struct node* head = NULL;
    for (int i = n - 1; i >= 0; i--) {
        struct node* nd = (struct node*)malloc(sizeof(struct node));
        nd->Data = a[i];
        nd->Next = head;
        head = nd;
    }
    return head;
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
    int a[] = {1, 1, 2, 3, 3, 3, 1};
    struct node* L = fromArray(a, 7);

    printf("Before: ");
    printList(L);
    removeConsecutiveDuplicates(L);
    printf("After:  ");
    printList(L); /* 1 2 3 1 */

    freeList(L);
    return 0;
}
