/*
 * Sum Tree: every non-leaf node equals the sum of ALL the nodes in its
 * left and right subtrees. Empty trees and leaves count as sum trees.
 *
 *          26
 *         /  \
 *       10    3        10 = 4 + 6,  3 = 3,  26 = (10+4+6) + (3+3)
 *      /  \    \
 *     4    6    3
 *
 * Note: this version is O(n^2) because sum() is called at every node.
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

int sum(TNode T) {
    if (T == NULL)
        return 0;

    return T->Element + sum(T->Left) + sum(T->Right);
}

int SumTree(TNode T) {
    if (T == NULL)
        return 1;

    if (T->Left == NULL && T->Right == NULL)
        return 1;

    return sum(T->Left) + sum(T->Right) == T->Element &&
           SumTree(T->Left) && SumTree(T->Right);
}

TNode newNode(int x, TNode left, TNode right) {
    TNode n = (TNode)malloc(sizeof(struct node));
    n->Element = x;
    n->Left = left;
    n->Right = right;
    return n;
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
    TNode T = newNode(26,
                      newNode(10, newNode(4, NULL, NULL), newNode(6, NULL, NULL)),
                      newNode(3, NULL, newNode(3, NULL, NULL)));
    printf("Is sum tree? %d\n", SumTree(T)); /* 1 */

    T->Element = 25;
    printf("After changing root to 25: %d\n", SumTree(T)); /* 0 */

    MakeEmpty(T);
    return 0;
}
