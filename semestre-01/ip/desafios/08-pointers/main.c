#include <stdio.h>

void update(int *a,int *b) {
    int a_int = *a;

    (*a) += (*b);

    if (a_int > *b) {
        (*b) = a_int - (*b);
    } else {
        (*b) -= a_int;
    }
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}
