/*
 * Count the subtrees whose values are ALL inside the range [n, m].
 *
 * Post-order: first check the left and right subtrees, then the node.
 * A node starts a valid subtree only if both of its subtrees are valid
 * and its own value is in the range.
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

/* Returns 1 if the subtree rooted at T is fully inside [n, m]. */
int isSubTree(TNode T, int n, int m, int* count) {
    if (T == NULL)
        return 1;

    int left = isSubTree(T->Left, n, m, count);
    int right = isSubTree(T->Right, n, m, count);

    if (left == 1 && right == 1 && T->Element >= n && T->Element <= m) {
        (*count)++;
        return 1;
    }
    return 0;
}

int numOfTrees(TNode T, int n, int m) {
    int count = 0;
    isSubTree(T, n, m, &count);  /* fixed: was calling countSubtrees(), which does not exist */
    return count;
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

    /* range [15, 45]: subtrees {20}, {40}, {30,20,40} -> 3 */
    printf("Subtrees in [15, 45] = %d\n", numOfTrees(T, 15, 45));
    /* range [0, 100]: every node is a valid subtree -> 7 */
    printf("Subtrees in [0, 100] = %d\n", numOfTrees(T, 0, 100));

    MakeEmpty(T);
    return 0;
}
