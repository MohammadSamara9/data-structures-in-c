/*
 * Lecture 3 - Linked List
 * The linked list ADT from the slides (with a header / dummy node).
 *
 *   L -> [header] -> [Data|Next] -> [Data|Next] -> NULL
 *
 * Fixed from the slides:
 *  - Find: "X = X->Next" must be "P = P->Next" (X is an int).
 *  - Delete and DeleteList: "struct node* P, temp;" makes temp a struct,
 *    not a pointer. It must be "struct node *P, *temp;".
 *  - IsLast: the body was empty on the slide.
 *  - MakeEmpty: return NULL when malloc fails (instead of using L).
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int Data;
    struct node* Next;
};

void DeleteList(struct node* L);

/* Creates an empty list (only the header node) */
struct node* MakeEmpty(struct node* L) {
    if (L != NULL)
        DeleteList(L);
    L = (struct node*)malloc(sizeof(struct node));
    if (L == NULL) {
        printf("Out of memory!\n");
        return NULL;
    }
    L->Next = NULL;
    return L;
}

/* Checks if the list is empty */
int IsEmpty(struct node* L) {
    return L->Next == NULL;
}

/* Checks if a given node is the last node in the linked list */
int IsLast(struct node* P, struct node* L) {
    (void)L; /* L is not needed here */
    return P->Next == NULL;
}

/* Returns a pointer to the node that has X, or NULL */
struct node* Find(int X, struct node* L) {
    struct node* P;
    P = L->Next;
    while (P != NULL && P->Data != X)
        P = P->Next;
    return P;
}

/* Returns the node BEFORE the one that has X.
   If X is not found, the Next field of the returned node is NULL. */
struct node* FindPrevious(int X, struct node* L) {
    struct node* P;
    P = L;
    while (P->Next != NULL && P->Next->Data != X)
        P = P->Next;
    return P;
}

/* Deletes the first occurrence of X */
void Delete(int X, struct node* L) {
    struct node *P, *temp;
    P = FindPrevious(X, L);
    if (!IsLast(P, L)) {
        temp = P->Next;
        P->Next = temp->Next; /* bypass the deleted cell */
        free(temp);
    }
}

/* Inserts X after position P */
void Insert(int X, struct node* L, struct node* P) {
    (void)L;
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->Data = X;
    temp->Next = P->Next;
    P->Next = temp;
}

void PrintList(struct node* L) {
    struct node* P = L;
    if (IsEmpty(L))
        printf("Empty list\n");
    else {
        do {
            P = P->Next;
            printf("%d\t", P->Data);
        } while (!IsLast(P, L));
        printf("\n");
    }
}

/* Deletes all the elements (keeps the header) */
void DeleteList(struct node* L) {
    struct node *P, *temp;
    P = L->Next;
    L->Next = NULL;
    while (P != NULL) {
        temp = P->Next;
        free(P);
        P = temp;
    }
}

/* Size of a linked list */
int size(struct node* L) {
    struct node* p = L->Next;
    int count = 0;
    while (p != NULL) {
        count += 1;
        p = p->Next;
    }
    return count;
}

int main(void) {
    struct node* L = MakeEmpty(NULL);

    /* insert 10, 20, 30 at the end */
    struct node* last = L;
    for (int x = 10; x <= 30; x += 10) {
        Insert(x, L, last);
        last = last->Next;
    }
    Insert(5, L, L); /* insert at the start */

    printf("List: ");
    PrintList(L);                         /* 5 10 20 30 */
    printf("Size: %d\n", size(L));        /* 4 */
    printf("Find(20): %s\n", Find(20, L) ? "found" : "not found");

    Delete(20, L);
    printf("After Delete(20): ");
    PrintList(L);                         /* 5 10 30 */

    DeleteList(L);
    printf("After DeleteList: ");
    PrintList(L);                         /* Empty list */

    free(L); /* free the header */
    return 0;
}
