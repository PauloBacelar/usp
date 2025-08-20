#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


void get_integer_name(int n) {
    if (n == 1) {
        printf("one\n");
    } else if (n == 2) {
        printf("two\n");
    } else if (n == 3) {
        printf("three\n");
    } else if (n == 4) {
        printf("four\n");
    } else if (n == 5) {
        printf("five\n");
    } else if (n == 6) {
        printf("six\n");
    } else if (n == 7) {
        printf("seven\n");
    } else if (n == 8) {
        printf("eight\n");
    } else if (n == 9) {
        printf("nine\n");
    }
}


int main() {
    int a, b;
    scanf("%d\n%d", &a, &b);
  	for (int i = a; i <= b; i++) {
        if (i <= 9) {
            get_integer_name(i);
        } else if (i > 9) {
            if (i % 2 == 0) {
                printf("even\n");
            } else {
                printf("odd\n");
            }
        }
    }

    return 0;
}

