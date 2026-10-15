/*
 * Mirror a binary tree: swap the left and right child of every node.
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

void mirror(TNode T) {
    if (T == NULL)
        return;

    TNode temp = T->Left;
    T->Left = T->Right;
    T->Right = temp;

    mirror(T->Left);
    mirror(T->Right);
}

void inorder(TNode T) {
    if (T == NULL)
        return;
    inorder(T->Left);
    printf("%d ", T->Element);
    inorder(T->Right);
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

    printf("Inorder before: ");
    inorder(T); /* 20 30 40 50 60 70 80 */
    mirror(T);
    printf("\nInorder after:  ");
    inorder(T); /* 80 70 60 50 40 30 20 */
    printf("\n");

    MakeEmpty(T);
    return 0;
}
