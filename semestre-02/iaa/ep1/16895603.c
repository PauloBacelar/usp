#include <stdlib.h>
#include <stdio.h>


void preencher_matriz_ilhas(int** matriz, int linhas, int colunas, FILE* arquivo) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fscanf(arquivo, "%d", &matriz[i][j]);
        }
    }
}

void preencher_matriz_vizinhos(int matriz[4][2], int linha, int coluna) {
    matriz[0][0] = linha - 1;
    matriz[0][1] = coluna;

    matriz[1][0] = linha;
    matriz[1][1] = coluna + 1;

    matriz[2][0] = linha + 1;
    matriz[2][1] = coluna;

    matriz[3][0] = linha;
    matriz[3][1] = coluna - 1;
}


int deve_checar_vizinhos(int** matrizIlhas, int** matrizVisitas, int linha, int coluna) {
    return (matrizIlhas[linha][coluna] != 0) && (matrizVisitas[linha][coluna] == 0);
}


int posicao_eh_valida(int linha, int coluna, int linhas, int colunas) {
    return (linha >= 0) && (coluna >= 0) && (linha < linhas) && (coluna < colunas);
}


void checar_vizinhos(int** matrizIlhas, int** matrizVisitas, int linhas, int colunas, int linha, int coluna, int* profundidadeIlha) {
    *profundidadeIlha += matrizIlhas[linha][coluna];    
    matrizVisitas[linha][coluna] = 1;

    int vizinhos[4][2];
    preencher_matriz_vizinhos(vizinhos, linha, coluna);

    for (int i = 0; i < 4; i++) {
        int x = vizinhos[i][0];
        int y = vizinhos[i][1];

        if (posicao_eh_valida(x, y, linhas, colunas) && deve_checar_vizinhos(matrizIlhas, matrizVisitas, x, y)) {
            checar_vizinhos(matrizIlhas, matrizVisitas, linhas, colunas, x, y, profundidadeIlha);
        }
    }
}


int print_soma_profundidades(int* profundidades, int profundidade, int quantidadeIlhas, int indice, int somaAtual, int* solucao) {
    if (somaAtual == profundidade) {
        for (int i = 0; i < profundidade; i++) {
            if (solucao[i] != 0 && profundidades[i] != 0) {
                printf("%d ", profundidades[i]);
            }
        }

        return 1;
    }

    if (indice == quantidadeIlhas || somaAtual > profundidade) {
        return 0;
    }

    solucao[indice] = 1;
    if (print_soma_profundidades(profundidades, profundidade, quantidadeIlhas, indice + 1, somaAtual + profundidades[indice], solucao)) {
        return 1;
    }

    solucao[indice] = 0;
    if (print_soma_profundidades(profundidades, profundidade, quantidadeIlhas, indice + 1, somaAtual, solucao)) {
        return 1;
    }

    return 0;
}


int percorrer_matriz(int** matrizIlhas, int linhas, int colunas, int profundidade) {
    int** matrizVisitas = (int**) malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        matrizVisitas[i] = (int*) calloc(colunas, sizeof(int));
    }
    
    int quantidadeIlhas = 0;
    int* profundidades = (int*) calloc(linhas * colunas, sizeof(int));

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (deve_checar_vizinhos(matrizIlhas, matrizVisitas, i, j)) {
                int profundidadeIlha = 0;
                quantidadeIlhas++;

                checar_vizinhos(matrizIlhas, matrizVisitas, linhas, colunas, i, j, &profundidadeIlha);
                
                if (profundidadeIlha > 0 && profundidadeIlha < 6) {
                    profundidadeIlha = 1;
                } else {
                    profundidadeIlha /= 6;
                }

                profundidades[quantidadeIlhas - 1] = profundidadeIlha;
            }

            matrizVisitas[i][j] = 1;
        }
    }

    printf("%d\n", quantidadeIlhas);
    for (int i = 0; i < quantidadeIlhas; i++) {
        printf("%d ", profundidades[i]);
    }
    printf("\n");

    int encontrou = 0;
    int* solucao = malloc(quantidadeIlhas * sizeof(int));

    if (!print_soma_profundidades(profundidades, profundidade, quantidadeIlhas, 0, 0, solucao)) {
        printf("Nao ha resposta valida!");
    }

    for (int i = 0; i < linhas; i++) {
        free(matrizVisitas[i]);
    }
    free(matrizVisitas);
    free(profundidades);
    free(solucao);
}


int main(int argc, char *argv[]) {
    int profundidade = atoi(argv[1]);
    int numero_linhas = atoi(argv[2]);
    int numero_colunas = atoi(argv[3]);
    FILE* arquivo = fopen(argv[4], "r");

    int** matrizIlhas = (int**) malloc(numero_linhas * sizeof(int*));
    for (int i = 0; i < numero_linhas; i++) {
        matrizIlhas[i] = (int*) malloc(numero_colunas * sizeof(int));
    }

    preencher_matriz_ilhas(matrizIlhas, numero_linhas, numero_colunas, arquivo);
    percorrer_matriz(matrizIlhas, numero_linhas, numero_colunas, profundidade);

    for (int i = 0; i < numero_linhas; i++) {
        free(matrizIlhas[i]);
    }
    free(matrizIlhas);
    fclose(arquivo);

    return 0;
}