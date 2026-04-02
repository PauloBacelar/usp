#include <stdio.h>
#include <stdlib.h>


void print_array(int* A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }

    printf("\n");
}


void insertion_sort(int* A, int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;

        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }

        A[j + 1] = key;
    } 
}


void bubble_sort(int* A, int n) {
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (A[j] > A[j + 1]) {
                int tmp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = tmp;
            }
        }
    }

    print_array(A, n);
}


int main() {
    int n = 6;
    int* A = (int *) malloc(n * sizeof(int));

    A[0] = 31;
    A[1] = 41;
    A[2] = 59;
    A[3] = 26;
    A[4] = 41;
    A[5] = 58;

    print_array(A, n);

    // insertion_sort(A, n);
    bubble_sort(A, n);
    print_array(A, n);

    return 0;
}