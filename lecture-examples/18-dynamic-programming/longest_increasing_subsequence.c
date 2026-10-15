/*
 * Lecture 18 - Dynamic Programming
 * Longest Increasing Subsequence (LIS).
 *
 * For each element we have two choices:
 *   1. exclude it and continue with the rest
 *   2. include it, only if it is greater than the previous element taken
 * and we return the maximum of the two.
 *
 * Example from the slides: {2,4,3,5,1,7,6,9,8} -> 5, e.g. {2,4,5,6,8}
 *
 * Fixed from the slide: max() does not exist in C, so it is written here.
 * The first call uses INT_MIN as "previous", so any first element can be taken.
 */
#include <stdio.h>
#include <limits.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int LIS(int arr[], int i, int n, int prev) {
    /* Base case - empty list */
    if (i == n)
        return 0;

    /* case 1 - exclude the current element and process the remaining elements */
    int exclude = LIS(arr, i + 1, n, prev);

    /* case 2 - include the current element if it is greater than the previous
       element in the LIS */
    int include = 0;
    if (arr[i] > prev)
        include = 1 + LIS(arr, i + 1, n, arr[i]);

    /* return maximum of above two choices */
    return max(include, exclude);
}

int main(void) {
    int s1[] = {2, 4, 3, 5, 1, 7, 6, 9, 8};
    int s2[] = {3, 2, 6, 4, 5, 1};
    int s3[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};

    printf("LIS of {2,4,3,5,1,7,6,9,8}          = %d\n", LIS(s1, 0, 9, INT_MIN)); /* 5 */
    printf("LIS of {3,2,6,4,5,1}                = %d\n", LIS(s2, 0, 6, INT_MIN)); /* 3 */
    printf("LIS of {10,22,9,33,21,50,41,60,80}  = %d\n", LIS(s3, 0, 9, INT_MIN)); /* 6 */
    return 0;
}
