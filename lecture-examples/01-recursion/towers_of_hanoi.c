/*
 * Lecture 1 - Recursion
 * Towers of Hanoi.
 *
 * move(N, first, last, aux):
 *   1. move N-1 disks from first to aux   (use last as the helper)
 *   2. move 1 disk   from first to last
 *   3. move N-1 disks from aux to last    (use first as the helper)
 *
 * The minimum number of moves is 2^n - 1.
 */
#include <stdio.h>

void move(int N, char first, char last, char aux) {
    if (N > 0) {
        move(N - 1, first, aux, last);
        printf("Move disk %d from %c to %c\n", N, first, last); /* move(1, first, last, aux); */
        move(N - 1, aux, last, first);
    }
}

int main(void) {
    int numberOfDisks;

    printf("Please enter a number:\n");
    scanf("%d", &numberOfDisks);

    move(numberOfDisks, 'A', 'C', 'B');

    return 0;
}
