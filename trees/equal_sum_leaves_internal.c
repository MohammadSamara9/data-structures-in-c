/*
 * Equisum: is the sum of the LEAVES equal to the sum of the INTERNAL
 * nodes (nodes that have at least one child)?
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int Element;
    struct node* Left;
    struct node* Right;
};

typedef struct node* TNode;

/* ---------- solution ---------- */

int sumLeaves(TNode T) {
    if (T == NULL)
        return 0;

    if (T->Left == NULL && T->Right == NULL)
        return T->Element;

    return sumLeaves(T->Left) + sumLeaves(T->Right);
}

int sumInternal(TNode T) {
    if (T == NULL)
        return 0;

    if (T->Left == NULL && T->Right == NULL)
        return 0;

    return T->Element + sumInternal(T->Left) + sumInternal(T->Right);
}

int Equisum(TNode T) {
    return sumLeaves(T) == sumInternal(T);
}

/* ---------- helpers for the demo ---------- */

TNode Insert(int X, TNode T) {  /* BST insert */
    if (T == NULL) {
        T = (TNode)malloc(sizeof(struct node));
        T->Element = X;
        T->Left = T->Right = NULL;
    } else if (X < T->Element) {
        T->Left = Insert(X, T->Left);
    } else if (X > T->Element) {
        T->Right = Insert(X, T->Right);
    }
    return T;
}

TNode MakeEmpty(TNode T) {
    if (T != NULL) {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

/* Builds this BST:
 *            50
 *          /    \
 *        30      70
 *       /  \    /  \
 *     20   40  60   80
 */
TNode sampleTree(void) {
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    TNode T = NULL;
    for (int i = 0; i < 7; i++)
        T = Insert(values[i], T);
    return T;
}

int main(void) {
    TNode T = sampleTree();
    /* leaves: 20+40+60+80 = 200, internal: 50+30+70 = 150 */
    printf("Leaves = %d, Internal = %d, Equisum = %d\n",
           sumLeaves(T), sumInternal(T), Equisum(T)); /* 0 */
    MakeEmpty(T);

    /*        10
     *       /  \
     *      4    6     leaves: 4+6 = 10, internal: 10  -> Equisum = 1 */
    T = Insert(10, NULL);
    T = Insert(4, T);
    T = Insert(16, T);
    T->Right->Element = 6; /* set by hand, it is not a BST anymore */
    printf("Second tree Equisum = %d\n", Equisum(T)); /* 1 */
    MakeEmpty(T);
    return 0;
}
