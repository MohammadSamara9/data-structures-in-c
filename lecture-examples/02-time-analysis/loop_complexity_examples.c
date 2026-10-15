/*
 * Lecture 2 - Time Analysis
 * The loop examples from the "Loops and Big-O Notation" slides.
 *
 * Each function runs one code fragment from the slides and COUNTS how many
 * times the innermost statement runs. Run it and watch how the count grows
 * when n doubles: that is the Big-O in action.
 *
 * Fixed from the slides:
 *  - page 39: "for (int i = n; i > 0; i += c)" never stops (i keeps growing),
 *             it should be "i -= c".
 *  - page 41: pow() needs math.h and -lm, so i = i * i is used instead (c = 2).
 */
#include <stdio.h>

#define C 2 /* "c is a positive integer constant" */

/* O(n): the loop variable changes by a constant amount */
long linear(int n) {
    long count = 0;
    for (int i = 1; i <= n; i += C)
        count++;
    return count;
}

/* O(n^2): nested loops */
long quadratic(int n) {
    long count = 0;
    for (int i = 1; i <= n; i += C)
        for (int j = 1; j <= n; j += C)
            count++;
    return count;
}

/* O(n^2): the inner loop runs N, N-1, N-2, ... times */
long triangle(int N) {
    long count = 0;
    for (int i = 0; i < N; i++)
        for (int j = N; j > i; j--)
            count++;
    return count;
}

/* O(log n): the loop variable is multiplied by a constant */
long logarithmic(int n) {
    long count = 0;
    for (int i = 1; i <= n; i *= C)
        count++;
    return count;
}

/* O(log log n): the loop variable grows exponentially (i = i^c) */
long log_log(int n) {
    long count = 0;
    for (long i = 2; i <= n; i = i * i)
        count++;
    return count;
}

/* O(n^3): the inner loop runs 0 + n + 2n + ... + n(n-1) times */
long cubic(int n) {
    long b = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i * n; j++)
            b++;
    return b;
}

/* O(n^2 log n): while loop halves k, the inner loop is n^2 */
long n2_log_n(int n) {
    long a = 0;
    long k = (long)n * n;
    while (k > 1) {
        for (long j = 0; j < (long)n * n; j++)
            a++;
        k = k / 2;
    }
    return a;
}

/* O((log n)^3): three nested loops that each halve */
long log_cubed(int n) {
    long count = 0;
    for (int i = n; i > 0; i = i / 2)
        for (int j = n; j > 0; j = j / 2)
            for (int k = n; k > 0; k = k / 2)
                count++;
    return count;
}

int main(void) {
    printf("%8s %10s %10s %10s %8s %8s %12s %14s %10s\n",
           "n", "O(n)", "O(n^2)", "triangle", "O(logn)", "loglog", "O(n^3)", "O(n^2 logn)", "(logn)^3");

    for (int n = 16; n <= 256; n *= 2)
        printf("%8d %10ld %10ld %10ld %8ld %8ld %12ld %14ld %10ld\n",
               n, linear(n), quadratic(n), triangle(n), logarithmic(n),
               log_log(n), cubic(n), n2_log_n(n), log_cubed(n));

    return 0;
}
