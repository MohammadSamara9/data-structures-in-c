/*
 * Union of two sorted lists (no repeated common values).
 *
 * Lists use a header (dummy) node: the real data starts at L->Next.
 * Same idea as the merge step of merge sort.
 *
 * Time: O(n + m)
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int Data;
    struct node* Next;
};

typedef struct node* List;

List MakeEmpty(void) {
    List L = (List)malloc(sizeof(struct node));
    L->Next = NULL;
    return L;
}

/* Inserts X after position P. */
void Insert(int X, List L, struct node* P) {
    (void)L;
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->Data = X;
    temp->Next = P->Next;
    P->Next = temp;
}

List Union(List L1, List L2) {
    struct node* p1 = L1->Next;
    struct node* p2 = L2->Next;

    List result = MakeEmpty();
    struct node* last = result;

    while (p1 != NULL && p2 != NULL) {
        if (p1->Data < p2->Data) {
            Insert(p1->Data, result, last);
            p1 = p1->Next;
        } else if (p2->Data < p1->Data) {
            Insert(p2->Data, result, last);
            p2 = p2->Next;
        } else { /* equal: add it once */
            Insert(p1->Data, result, last);
            p1 = p1->Next;
            p2 = p2->Next;
        }
        last = last->Next;
    }

    while (p1 != NULL) {
        Insert(p1->Data, result, last);
        p1 = p1->Next;
        last = last->Next;
    }

    while (p2 != NULL) {
        Insert(p2->Data, result, last);
        p2 = p2->Next;
        last = last->Next;
    }

    return result;
}

/* ---------- helpers for the demo ---------- */

List fromArray(const int a[], int n) {
    List L = MakeEmpty();
    struct node* last = L;
    for (int i = 0; i < n; i++) {
        Insert(a[i], L, last);
        last = last->Next;
    }
    return L;
}

void printList(List L) {
    for (struct node* p = L->Next; p != NULL; p = p->Next)
        printf("%d ", p->Data);
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
    int a[] = {1, 3, 5, 7};
    int b[] = {2, 3, 6, 7, 9};

    List L1 = fromArray(a, 4);
    List L2 = fromArray(b, 5);
    List R = Union(L1, L2);

    printf("Union: ");
    printList(R); /* 1 2 3 5 6 7 9 */

    freeList(L1);
    freeList(L2);
    freeList(R);
    return 0;
}
