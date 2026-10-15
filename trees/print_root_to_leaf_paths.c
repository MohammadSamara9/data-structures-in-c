/*
 * Print every path from the root to a leaf.
 *
 * Keep the current path in an array. When we reach a leaf, print it.
 * pathLen is passed by value, so each recursive call has its own length
 * and we do not need to "undo" anything when going back up.
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

void printPath(TNode T, int path[], int pathLen) {
    if (T == NULL)
        return;  /* fixed: was "return 0;" inside a void function */

    path[pathLen] = T->Element;
    pathLen++;

    if (T->Left == NULL && T->Right == NULL) {
        /* fixed: numbers were printed glued together with no separator */
        for (int i = 0; i < pathLen; i++)
            printf(i == 0 ? "%d" : " -> %d", path[i]);
        printf("\n");
    } else {
        printPath(T->Left, path, pathLen);
        printPath(T->Right, path, pathLen);
    }
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
    int path[100];

    printPath(T, path, 0);
    /*
     * 50 -> 30 -> 20
     * 50 -> 30 -> 40
     * 50 -> 70 -> 60
     * 50 -> 70 -> 80
     */

    MakeEmpty(T);
    return 0;
}
