/*
 * Lecture 1 - Recursion
 * Example: a recursive function that counts to 10.
 *
 * Fixed from the slide: print -> printf, main() was missing "{",
 * and the curly quotes were replaced with normal quotes.
 */
#include <stdio.h>

void count_to_ten(int count) {
    if (count <= 10) {               /* base case: stop after 10 */
        printf("%d\t", count);
        count_to_ten(count + 1);     /* get closer to the base case */
    }
}

int main(void) {
    count_to_ten(1);
    printf("\n");
    return 0;
}
