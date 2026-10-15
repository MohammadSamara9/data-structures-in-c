/*
 * Lecture 8 - Binary Search Trees
 * The BST ADT from the slides: MakeEmpty, Find, FindMin, FindMax, Insert, Delete.
 * Both the recursive and the iterative FindMin / FindMax are included.
 *
 * Fixed from the slides:
 *  - Find and Insert used "T->element" (lowercase) but the struct field is
 *    "Element".
 */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int Element;
    struct Node* Left;
    struct Node* Right;
};
typedef struct Node* TNode;

/* used to initialise a tree (and to free it) */
TNode MakeEmpty(TNode T) {
    if (T != NULL) {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

TNode Find(int X, TNode T) {
    if (T == NULL)
        return NULL;
    else if (X < T->Element)
        return Find(X, T->Left);
    else if (X > T->Element)
        return Find(X, T->Right);
    else
        return T;
}

/* recursive implementation of FindMin */
TNode FindMin(TNode T) {
    if (T == NULL)
        return NULL;
    else if (T->Left == NULL)
        return T;
    else
        return FindMin(T->Left);
}

/* non-recursive implementation of FindMin */
TNode FindMinIterative(TNode T) {
    if (T != NULL)
        while (T->Left != NULL)
            T = T->Left;
    return T;
}

/* recursive implementation of FindMax */
TNode FindMax(TNode T) {
    if (T == NULL)
        return NULL;
    else if (T->Right == NULL)
        return T;
    else
        return FindMax(T->Right);
}

/* non-recursive implementation of FindMax */
TNode FindMaxIterative(TNode T) {
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;
    return T;
}

TNode Insert(int X, TNode T) {
    if (T == NULL) {
        /* create and return a 1-node tree */
        T = (struct Node*)malloc(sizeof(struct Node));
        if (T == NULL)
            printf("Out of space\n");
        else {
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    } else if (X < T->Element)
        T->Left = Insert(X, T->Left);
    else if (X > T->Element)
        T->Right = Insert(X, T->Right);
    /* else, X is in the tree already; do nothing */
    return T;
}

TNode Delete(int X, TNode T) {
    TNode TmpCell;
    if (T == NULL)
        printf("Element not found\n");
    else if (X < T->Element) /* Go left */
        T->Left = Delete(X, T->Left);
    else if (X > T->Element) /* Go right */
        T->Right = Delete(X, T->Right);
    else /* Found element to be deleted */
        if (T->Left && T->Right) { /* Two children */
            /* Replace with smallest in right subtree */
            TmpCell = FindMin(T->Right);
            T->Element = TmpCell->Element;
            T->Right = Delete(T->Element, T->Right);
        } else { /* One or zero children */
            TmpCell = T;
            if (T->Left == NULL) /* Also handles 0 children */
                T = T->Right;
            else if (T->Right == NULL)
                T = T->Left;
            free(TmpCell);
        }
    return T;
}

void PrintInOrder(TNode T) {
    if (T != NULL) {
        PrintInOrder(T->Left);
        printf("%d ", T->Element);
        PrintInOrder(T->Right);
    }
}

int main(void) {
    TNode T = MakeEmpty(NULL);
    int values[] = {6, 2, 8, 1, 4, 3, 7, 9};

    for (int i = 0; i < 8; i++)
        T = Insert(values[i], T);

    printf("In-order: ");
    PrintInOrder(T); /* 1 2 3 4 6 7 8 9 */
    printf("\nMin = %d (iterative: %d)\n", FindMin(T)->Element, FindMinIterative(T)->Element);
    printf("Max = %d (iterative: %d)\n", FindMax(T)->Element, FindMaxIterative(T)->Element);
    printf("Find(4): %s\n", Find(4, T) ? "found" : "not found");

    T = Delete(2, T); /* 2 has two children */
    printf("After Delete(2): ");
    PrintInOrder(T); /* 1 3 4 6 7 8 9 */
    printf("\n");

    T = MakeEmpty(T);
    return 0;
}
