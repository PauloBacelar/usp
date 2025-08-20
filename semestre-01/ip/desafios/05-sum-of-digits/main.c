#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
	
    int n;
    scanf("%d", &n);
    
    int soma = 0;
    for (int i = 10000; i >= 1; i *= 0.1) {
        int digito = (n / i) % 10;
        soma += digito;
    }
    
    printf("%d", soma);
    
    return 0;
}
