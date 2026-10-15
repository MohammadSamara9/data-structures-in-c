/*
 * Print a BST from the largest value to the smallest.
 *
 * Reverse in-order traversal: Right -> Root -> Left.
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

void PrintLargestToSmallest(TNode T) {
    if (T == NULL)
        return;

    PrintLargestToSmallest(T->Right);
    printf("%d ", T->Element);
    PrintLargestToSmallest(T->Left);
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

    PrintLargestToSmallest(T); /* 80 70 60 50 40 30 20 */
    printf("\n");

    MakeEmpty(T);
    return 0;
}
