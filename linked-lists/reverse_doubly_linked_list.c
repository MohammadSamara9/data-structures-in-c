/*
 * Build a REVERSED COPY of a doubly linked list.
 * The original list is not changed.
 *
 * Idea: walk the original from the start and insert each value at the
 * FRONT of the new list, so the order ends up reversed.
 *
 * Time: O(n)   Space: O(n) for the new list
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int Data;
    struct node* Next;
    struct node* Prev;
};

typedef struct node* List;

List reverse(List head) {
    struct node* reversed = NULL;
    struct node* current = head;
    struct node* temp;

    while (current != NULL) {
        temp = (struct node*)malloc(sizeof(struct node));

        temp->Data = current->Data;
        temp->Prev = NULL;
        temp->Next = reversed;

        if (reversed != NULL)
            reversed->Prev = temp;

        reversed = temp;
        current = current->Next;
    }

    return reversed;
}

/* ---------- helpers for the demo ---------- */

List fromArray(const int a[], int n) {
    List head = NULL, last = NULL;
    for (int i = 0; i < n; i++) {
        struct node* nd = (struct node*)malloc(sizeof(struct node));
        nd->Data = a[i];
        nd->Next = NULL;
        nd->Prev = last;
        if (last == NULL)
            head = nd;
        else
            last->Next = nd;
        last = nd;
    }
    return head;
}

void printList(List L) {
    for (; L != NULL; L = L->Next)
        printf("%d ", L->Data);
    printf("\n");
}

void freeList(List L) {
    while (L != NULL) {
        struct node* next = L->Next;
        free(L);
        L = next;
    }
}

int main(void) {
    int a[] = {1, 2, 3, 4};
    List L = fromArray(a, 4);
    List R = reverse(L);

    printf("Original: ");
    printList(L);
    printf("Reversed: ");
    printList(R); /* 4 3 2 1 */

    freeList(L);
    freeList(R);
    return 0;
}
