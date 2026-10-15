/*
 * Lecture 13 - Hashing Strings
 * The three hash functions for string keys from the slides.
 *
 *  hash1: add the ASCII codes of all the characters.
 *         Problem: small values, and anagrams ("abc", "cba") collide.
 *  hash2: use only the first 3 characters: key[0] + key[1]*27 + key[2]*729
 *  hash3: hashValue = hashValue * 32 + char  (shift left by 5 = multiply by 32)
 *
 * Fixed from the slides:
 *  - hash1: the while loop was missing its closing "}".
 *  - hash2 was only a return line; it is wrapped in a function here.
 *  - hash3: the value can overflow and become negative for long strings,
 *    so unsigned int is used, then the result is taken mod TableSize.
 */
#include <stdio.h>

int hash1(char* key, int TableSize) {
    int hashValue = 0;
    while (*key != '\0') {
        hashValue += *key++;
    }
    return (hashValue % TableSize);
}

int hash2(char* key, int TableSize) {
    /* assumes the key has at least 3 characters */
    return ((int)key[0] + (int)key[1] * 27 + (int)key[2] * 729) % TableSize;
}

int hash3(char* key, int TableSize) {
    unsigned int hashValue = 0;
    while (*key != '\0') {
        hashValue = (hashValue << 5) + *key++;
    }
    return (int)(hashValue % TableSize);
}

int main(void) {
    char* keys[] = {"abc", "cba", "bca", "hello", "world", "birzeit"};
    int TableSize = 101;

    printf("%-10s %6s %6s %6s\n", "key", "hash1", "hash2", "hash3");
    for (int i = 0; i < 6; i++)
        printf("%-10s %6d %6d %6d\n", keys[i],
               hash1(keys[i], TableSize), hash2(keys[i], TableSize), hash3(keys[i], TableSize));

    printf("\nNotice: hash1 gives the same value for abc, cba and bca (collision).\n");
    return 0;
}
