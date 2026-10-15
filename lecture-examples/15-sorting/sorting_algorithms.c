/*
 * Lecture 15 - Sorting
 * The sorting algorithms that have code on the slides:
 *   Insertion Sort   O(n^2)
 *   Selection Sort   O(n^2)
 *   Merge Sort       O(n log n)
 *   Shell Sort       depends on the gaps, about O(n^1.5) with n/2, n/4, ...
 *
 * Fixed from the slides:
 *  - SelectionSort: one closing "}" was missing.
 *  - MergeSort: called "mergeSort" (lowercase m) and "merge", but merge()
 *    was not on the slides, so it is written here.
 *  - shellSort: the parameter was "m" but the body used "n" and "num".
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InsertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) { /* shift elements */
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void SelectionSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[i]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
    }
}

/* Merges the two sorted halves arr[p..m] and arr[m+1..q] (not on the slides) */
void merge(int arr[], int p, int m, int q) {
    int n1 = m - p + 1, n2 = q - m;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    memcpy(L, arr + p, n1 * sizeof(int));
    memcpy(R, arr + m + 1, n2 * sizeof(int));

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void MergeSort(int arr[], int p, int q) {
    if (p < q) {
        /* Same as (p+q)/2, but avoids overflow for large p and q */
        int m = p + (q - p) / 2;
        /* Sort first and second halves */
        MergeSort(arr, p, m);
        MergeSort(arr, m + 1, q);
        merge(arr, p, m, q);
    }
}

void shellSort(int arr[], int n) {
    int inc, j, k, temp;
    for (inc = n / 2; inc > 0; inc /= 2) {
        for (j = inc; j < n; j++) {
            for (k = j - inc; k >= 0; k -= inc) {
                if (arr[k + inc] >= arr[k])
                    break;
                else {
                    temp = arr[k];
                    arr[k] = arr[k + inc];
                    arr[k + inc] = temp;
                }
            }
        }
    }
}

void printArray(const char* name, int arr[], int n) {
    printf("%-15s", name);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void) {
    int original[] = {34, 8, 64, 51, 32, 21, 5, 17, 90, 1};
    int n = 10;
    int a[10];

    printArray("Original:", original, n);

    memcpy(a, original, sizeof(a));
    InsertionSort(a, n);
    printArray("Insertion:", a, n);

    memcpy(a, original, sizeof(a));
    SelectionSort(a, n);
    printArray("Selection:", a, n);

    memcpy(a, original, sizeof(a));
    MergeSort(a, 0, n - 1);
    printArray("Merge:", a, n);

    memcpy(a, original, sizeof(a));
    shellSort(a, n);
    printArray("Shell:", a, n);

    return 0;
}
