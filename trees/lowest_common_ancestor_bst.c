/*
 * Lowest Common Ancestor (LCA) of two values in a BST.
 *
 * If both values are smaller than the root, the LCA is in the left
 * subtree; if both are bigger, it is in the right subtree. Otherwise
 * the root is the point where they split, so it is the LCA.
 *
 * Time: O(h), h = height of the tree
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

TNode LCA(TNode T, int n1, int n2) {
    if (T == NULL)
        return NULL;

    if (n1 < T->Element && n2 < T->Element)
        return LCA(T->Left, n1, n2);

    if (n1 > T->Element && n2 > T->Element)
        return LCA(T->Right, n1, n2);

    return T;
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

    printf("LCA(20, 40) = %d\n", LCA(T, 20, 40)->Element); /* 30 */
    printf("LCA(20, 80) = %d\n", LCA(T, 20, 80)->Element); /* 50 */
    printf("LCA(60, 70) = %d\n", LCA(T, 60, 70)->Element); /* 70 */

    MakeEmpty(T);
    return 0;
}
