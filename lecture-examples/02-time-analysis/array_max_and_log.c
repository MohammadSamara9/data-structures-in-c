/*
 * Lecture 2 - Time Analysis
 * The two "primitive operations" examples from the slides, written in C.
 *
 * Example 1: ArrayMax(A, n)                      Total: 8n - 3 operations -> O(n)
 *     currentMax <- A[0]
 *     for i <- 1 to n-1 do
 *         if A[i] > currentMax then
 *             currentMax <- A[i]
 *     return currentMax
 *
 * Example 2: n is a power of 2, find m such that 2^m = n
 *                                                Total: 5 log2(n) + 2 -> O(log n)
 *     m <- 0
 *     while (n >= 2)
 *         n <- n / 2
 *         m++
 *     return m
 */
#include <stdio.h>

int ArrayMax(int A[], int n) {
    int currentMax = A[0];
    for (int i = 1; i <= n - 1; i++)
        if (A[i] > currentMax)
            currentMax = A[i];
    return currentMax;
}

int log2_of(int n) {
    int m = 0;
    while (n >= 2) {
        n = n / 2;
        m++;
    }
    return m;
}

int main(void) {
    int A[] = {7, 3, 19, 4, 11};
    printf("ArrayMax = %d\n", ArrayMax(A, 5)); /* 19 */
    printf("m for n = 64 is %d\n", log2_of(64)); /* 6, because 2^6 = 64 */
    return 0;
}
