/*
 * Sum of the K smallest values in a BST.
 *
 * In-order traversal visits the values from smallest to largest, so we
 * add the first K values we visit and stop early.
 *
 * Fixes from the first version:
 *  - it was a void function that did "return 0;" and never returned the sum
 *  - it used global variables, so calling it twice gave wrong answers
 *    -> now the count is passed as a pointer and the sum is returned
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

int sumKSmallestHelper(TNode T, int K, int* count) {
    if (T == NULL || *count >= K)
        return 0;

    int sum = sumKSmallestHelper(T->Left, K, count);

    if (*count < K) {
        sum += T->Element;
        (*count)++;
    }

    sum += sumKSmallestHelper(T->Right, K, count);
    return sum;
}

int sumKSmallest(TNode T, int K) {
    int count = 0;
    return sumKSmallestHelper(T, K, &count);
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

    printf("Sum of 3 smallest = %d\n", sumKSmallest(T, 3)); /* 20+30+40 = 90 */
    printf("Sum of 5 smallest = %d\n", sumKSmallest(T, 5)); /* 90+50+60 = 200 */

    MakeEmpty(T);
    return 0;
}
