/*
 * Lecture 1 - Recursion
 * Example: sum of the first n natural numbers using recursion.
 *
 *   sum(5) = 5 + sum(4)
 *          = 5 + 4 + sum(3)
 *          = 5 + 4 + 3 + sum(2)
 *          = 5 + 4 + 3 + 2 + sum(1)
 *          = 15
 */
#include <stdio.h>

int sum(int n) {
    if (n == 1)
        return n;
    else
        return n + sum(n - 1);
}

int main(void) {
    int num, add;
    printf("Enter a positive integer:\n");
    scanf("%d", &num);
    add = sum(num);
    printf("sum=%d\n", add);
    return 0;
}
