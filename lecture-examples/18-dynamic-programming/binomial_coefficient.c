/*
 * Lecture 18 - Dynamic Programming
 * Binomial coefficient C(n, m) = "n choose m" using Pascal's triangle:
 *
 *   C(i, 0) = 1,  C(i, i) = 1
 *   C(i, j) = C(i-1, j-1) + C(i-1, j)
 *
 * Fixed from the slide: MAXN was not defined in this example.
 */
#include <stdio.h>

#define MAXN 35

long binomial_coefficient(int n, int m) {
    int i, j;                  /* counters */
    long bc[MAXN][MAXN];       /* table of binomial coefficients */

    for (i = 0; i <= n; i++)
        bc[i][0] = 1;
    for (j = 0; j <= n; j++)
        bc[j][j] = 1;
    for (i = 1; i <= n; i++)
        for (j = 1; j < i; j++)
            bc[i][j] = bc[i - 1][j - 1] + bc[i - 1][j];

    return bc[n][m];
}

int main(void) {
    printf("C(5, 2)  = %ld\n", binomial_coefficient(5, 2));   /* 10 */
    printf("C(10, 3) = %ld\n", binomial_coefficient(10, 3));  /* 120 */

    printf("\nPascal's triangle:\n");
    for (int n = 0; n <= 6; n++) {
        for (int m = 0; m <= n; m++)
            printf("%4ld", binomial_coefficient(n, m));
        printf("\n");
    }
    return 0;
}
