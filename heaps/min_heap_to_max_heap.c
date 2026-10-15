/*
 * Convert a min-heap (stored in an array) into a max-heap.
 *
 * The array is 1-indexed: A[1] is the root, the children of i are
 * 2i and 2i+1. We ignore that it was a min-heap and simply build a
 * max-heap: call maxHeapify on every internal node from size/2 down to 1.
 *
 * Time: O(n)  (bottom-up heap building)
 */
#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Moves A[i] down until the subtree rooted at i is a max-heap. */
void maxHeapify(int A[], int i, int size) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest = i;

    if (left <= size && A[left] > A[largest])
        largest = left;

    if (right <= size && A[right] > A[largest])
        largest = right;

    if (largest != i) {
        swap(&A[i], &A[largest]);
        maxHeapify(A, largest, size);
    }
}

void convertMinToMaxHeap(int A[], int size) {
    for (int i = size / 2; i >= 1; i--)
        maxHeapify(A, i, size);
}

void printHeap(int A[], int size) {
    for (int i = 1; i <= size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main(void) {
    /* index 0 is not used */
    int A[] = {0, 3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
    int size = 10;

    printf("Min-heap: ");
    printHeap(A, size);

    convertMinToMaxHeap(A, size);

    printf("Max-heap: ");
    printHeap(A, size); /* root is now 20 */
    return 0;
}
