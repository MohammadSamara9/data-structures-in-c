/*
 * Height of a binary tree.
 *
 * Height of an empty tree = -1, height of a single node = 0.
 * height(T) = 1 + max(height(left), height(right))
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

int height(TNode T) {
    if (T == NULL)
        return -1;

    int leftHeight = height(T->Left);
    int rightHeight = height(T->Right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
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
    printf("Height = %d\n", height(T)); /* 2 */

    T = Insert(10, T); /* make the tree one level deeper */
    printf("Height after inserting 10 = %d\n", height(T)); /* 3 */

    MakeEmpty(T);
    return 0;
}
