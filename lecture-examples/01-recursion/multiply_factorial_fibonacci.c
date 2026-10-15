/*
 * Lecture 1 - Recursion
 * Three recursive functions from the slides:
 *   - multiply(m, n): m * n using only addition
 *   - factorial(n)
 *   - fibonnacci(n): 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
 */
#include <stdio.h>

/* m * n = m + m * (n - 1) */
int multiply(int m, int n) {
    int answer;

    if (n == 1)
        answer = m;
    else
        answer = m + multiply(m, n - 1);

    return answer;
}

/* n! = n * (n - 1)! and 0! = 1 */
int factorial(int n) {
    int answer;

    if (n == 0)
        answer = 1;
    else
        answer = n * factorial(n - 1);

    return answer;
}

/* Fib(n) = Fib(n - 1) + Fib(n - 2), Fib(0) = 0, Fib(1) = 1 */
int fibonnacci(int n) {
    int answer;

    if (n == 0 || n == 1)
        answer = n;
    else
        answer = fibonnacci(n - 1) + fibonnacci(n - 2);

    return answer;
}

int main(void) {
    printf("multiply(6, 4) = %d\n", multiply(6, 4));   /* 24 */
    printf("factorial(5)   = %d\n", factorial(5));     /* 120 */

    printf("Fibonacci: ");
    for (int i = 0; i < 10; i++)
        printf("%d ", fibonnacci(i));                  /* 0 1 1 2 3 5 8 13 21 34 */
    printf("\n");
    return 0;
}
