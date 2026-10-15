/*
 * Count the nodes in a BST whose value is greater than X.
 *
 * Uses the BST property to skip work:
 *  - if root <= X: nothing on the left can be bigger, go right only.
 *  - if root >  X: the root and its WHOLE right subtree are bigger,
 *                  then keep searching on the left.
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

int CountNodes(TNode T) {
    if (T == NULL)
        return 0;

    return 1 + CountNodes(T->Left) + CountNodes(T->Right);
}

int CountGreater(TNode T, int X) {
    if (T == NULL)
        return 0;

    if (T->Element <= X)  /* fixed: was T->element (lowercase), which does not compile */
        return CountGreater(T->Right, X);
    else
        return 1 + CountNodes(T->Right) + CountGreater(T->Left, X);
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

    printf("Nodes > 45 = %d\n", CountGreater(T, 45)); /* 50 60 70 80 -> 4 */
    printf("Nodes > 70 = %d\n", CountGreater(T, 70)); /* 80 -> 1 */
    printf("Nodes > 10 = %d\n", CountGreater(T, 10)); /* 7 */

    MakeEmpty(T);
    return 0;
}
