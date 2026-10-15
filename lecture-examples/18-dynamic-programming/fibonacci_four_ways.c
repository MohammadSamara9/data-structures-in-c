/*
 * Lecture 18 - Dynamic Programming
 * Fibonacci computed in 4 ways from the slides:
 *
 *   fib_r     plain recursion                    O(2^n)  very slow
 *   fib_c     recursion + caching (memoization)  O(n)
 *   fib_dp    dynamic programming with a table   O(n)
 *   fib_dp_2  DP keeping only the last 2 values  O(n) time, O(1) space
 *
 * Fixed from the slides:
 *  - fib_r: one extra ")" in the return line.
 *  - fib_c_driver: "UNKOWN" typo -> UNKNOWN.
 *  - The cache array is "long", so the functions return long too.
 */
#include <stdio.h>
#include <time.h>

#define MAXN 45     /* largest interesting n */
#define UNKNOWN -1  /* contents denote an empty cell */

long f[MAXN + 1];   /* array for caching computed fib values */

long fib_r(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fib_r(n - 1) + fib_r(n - 2);
}

long fib_c(int n) {
    if (f[n] == UNKNOWN)
        f[n] = fib_c(n - 1) + fib_c(n - 2);
    return f[n];
}

long fib_c_driver(int n) {
    int i;
    f[0] = 0;
    f[1] = 1;
    for (i = 2; i <= n; i++)
        f[i] = UNKNOWN;
    return fib_c(n);
}

long fib_dp(int n) {
    int i;
    long f[MAXN + 1]; /* array to cache computed fib values */
    f[0] = 0;
    f[1] = 1;
    for (i = 2; i <= n; i++)
        f[i] = f[i - 1] + f[i - 2];
    return f[n];
}

long fib_dp_2(int n) {
    int i;                    /* counter */
    long back2 = 0, back1 = 1; /* last two values of f[n] */
    long next;                /* placeholder for sum */
    if (n == 0)
        return 0;
    for (i = 2; i < n; i++) {
        next = back1 + back2;
        back2 = back1;
        back1 = next;
    }
    return back1 + back2;
}

int main(void) {
    int n = 40;
    clock_t start;

    start = clock();
    long r = fib_r(n);
    double tr = (double)(clock() - start) / CLOCKS_PER_SEC;

    printf("n = %d\n", n);
    printf("fib_r    = %ld   (%.3f seconds: plain recursion is slow!)\n", r, tr);
    printf("fib_c    = %ld\n", fib_c_driver(n));
    printf("fib_dp   = %ld\n", fib_dp(n));
    printf("fib_dp_2 = %ld\n", fib_dp_2(n));
    return 0;
}
