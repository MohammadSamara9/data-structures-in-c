/*
 * Count the leaves that hold an ODD value.
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

int get_odd_leaf_count(TNode T) {
    if (T == NULL)
        return 0;

    if (T->Left == NULL && T->Right == NULL)
        return (T->Element % 2 != 0) ? 1 : 0;

    return get_odd_leaf_count(T->Left) + get_odd_leaf_count(T->Right);
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
    int values[] = {50, 30, 70, 21, 40, 63, 81};
    TNode T = NULL;
    for (int i = 0; i < 7; i++)
        T = Insert(values[i], T);

    /* leaves: 21, 40, 63, 81 -> odd ones: 21, 63, 81 */
    printf("Odd leaves = %d\n", get_odd_leaf_count(T)); /* 3 */

    MakeEmpty(T);
    return 0;
}
