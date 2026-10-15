/*
 * Intersection of two sorted lists, keeping only the EVEN values.
 *
 * Lists use a header (dummy) node: the real data starts at L->Next.
 * Walk both lists together like in merge: move the pointer with the
 * smaller value; when the values are equal, it is a common value.
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

/* Creates an empty list (only the header node). */
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

List IntersectionEven(List L1, List L2) {
    List result = MakeEmpty();

    struct node* p1 = L1->Next;
    struct node* p2 = L2->Next;

    struct node* last = result;

    while (p1 != NULL && p2 != NULL) {
        if (p1->Data < p2->Data) {
            p1 = p1->Next;
        } else if (p2->Data < p1->Data) {
            p2 = p2->Next;
        } else {
            if (p1->Data % 2 == 0) {
                Insert(p1->Data, result, last);
                last = last->Next;
            }
            p1 = p1->Next;
            p2 = p2->Next;
        }
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
    int a[] = {1, 2, 4, 5, 6, 8};
    int b[] = {2, 3, 5, 6, 8, 10};

    List L1 = fromArray(a, 6);
    List L2 = fromArray(b, 6);
    List R = IntersectionEven(L1, L2);

    printf("L1: ");
    printList(L1);
    printf("L2: ");
    printList(L2);
    printf("Even intersection: ");
    printList(R); /* 2 6 8 */

    freeList(L1);
    freeList(L2);
    freeList(R);
    return 0;
}
