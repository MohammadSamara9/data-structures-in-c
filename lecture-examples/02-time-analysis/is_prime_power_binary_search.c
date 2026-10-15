/*
 * Lecture 2 - Time Analysis
 * Functions analyzed in the slides:
 *   - isPrime(n)              O(sqrt(n))
 *   - power(x, n)             O(log n)   (recursion that halves n)
 *   - BinarySearch(...)       O(log n)
 *
 * Fixed from the slides:
 *  - BinarySearch: "mid+i" was a typo, it must be "mid+1".
 *  - isPrime: "i <= sqrt(n)" is written as "i * i <= n" so no math library
 *    is needed (same meaning). "bool" needs <stdbool.h> in C.
 */
#include <stdio.h>
#include <stdbool.h>

bool isPrime(int n) {
    if (n == 2)
        return true;
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

/* x^n: square x and halve n each call */
int power(int x, int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    if (n % 2 == 0)
        return power(x * x, n / 2);
    else
        return power(x * x, n / 2) * x;
}

/* Search for key in a SORTED array. Returns its index, or -1. */
int BinarySearch(int A[], int lower, int upper, int key) {
    if (lower <= upper) {
        int mid = (lower + upper) / 2;
        if (A[mid] == key)
            return mid;
        else if (A[mid] < key)
            return BinarySearch(A, mid + 1, upper, key);
        else
            return BinarySearch(A, lower, mid - 1, key);
    } else
        return -1;
}

int main(void) {
    printf("Primes under 30: ");
    for (int i = 0; i < 30; i++)
        if (isPrime(i))
            printf("%d ", i);
    printf("\n");

    printf("power(2, 10) = %d\n", power(2, 10)); /* 1024 */
    printf("power(3, 5)  = %d\n", power(3, 5));  /* 243 */

    int A[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    printf("BinarySearch for 23 -> index %d\n", BinarySearch(A, 0, 9, 23)); /* 5 */
    printf("BinarySearch for 7  -> index %d\n", BinarySearch(A, 0, 9, 7));  /* -1 */
    return 0;
}
