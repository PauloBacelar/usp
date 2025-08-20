#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../baralho.h"

static int id;
static int num_jogadores;
static Carta mao[6];
static int num_cartas;
static Valor manilha_rodada;
int aposta_global;

int comparar_cartas_mao(const void* a, const void* b) {
    const Carta* c1 = (const Carta*)a;
    const Carta* c2 = (const Carta*)b;

    int eh_manilha1 = c1->valor == manilha_rodada;
    int eh_manilha2 = c2->valor == manilha_rodada;

    if (eh_manilha1 && !eh_manilha2) {
        return 1;
    }

    if (!eh_manilha1 && eh_manilha2) {
        return -1;
    } 

    if (c1->valor < c2->valor) {
        return -1;
    } 

    if (c1->valor > c2->valor) {
        return 1;
    } 

    if (c1->naipe < c2->naipe) {
        return -1;
    }

    if (c1->naipe > c2->naipe) {
        return 1;
    } 

    return 0;
}


int existe_manilha(const Carta* cartas, int qntd_cartas) {
    for (int i = 0; i < qntd_cartas; i++) {
        if (cartas[i].valor == manilha_rodada) {
            return 1;
        }
    }

    return 0;
}

Carta get_carta_mais_forte(const Carta* cartas, int qntd_cartas) {
    Carta maior_carta = cartas[0];
    int existe_manilha_bool = existe_manilha(cartas, qntd_cartas);
    
    if (existe_manilha_bool) {
        for (int i = 1; i < qntd_cartas; i++) {
            if (cartas[i].valor != manilha_rodada) {
                continue;
            }

            if (maior_carta.valor != manilha_rodada || (maior_carta.valor == manilha_rodada && cartas[i].naipe > maior_carta.naipe)) {
                maior_carta = cartas[i];
            }
        }
    } else {
        for (int i = 1; i < qntd_cartas; i++) {
            if (cartas[i].valor > maior_carta.valor ||
               (cartas[i].valor == maior_carta.valor && cartas[i].naipe > maior_carta.naipe)) {
                maior_carta = cartas[i];
            }
        }
    }

    return maior_carta;
}

int eh_possivel_ganhar(const Carta* mesa, const int num_na_mesa) {
    if (num_na_mesa == 0) {
        return 1;
    }

    if (existe_manilha(mao, num_cartas)) {
        return 1;
    } else if (existe_manilha(mesa, num_na_mesa)) {
        return 0;
    }

    Carta melhor_carta_na_mao = mao[num_cartas - 1];
    Carta melhor_carta_na_mesa = get_carta_mais_forte(mesa, num_na_mesa);
    return (melhor_carta_na_mao.valor > melhor_carta_na_mesa.valor) ||
    (melhor_carta_na_mao.valor == melhor_carta_na_mesa.valor && melhor_carta_na_mao.naipe > melhor_carta_na_mesa.naipe);
}

int round(double n) {
    return (int)(n + 0.5);
}

const char* nome_16895603() {
    return "Bacelar";
}

void iniciar_16895603(const int meu_id, const int total_jogadores) {
    id = meu_id;
    num_jogadores = total_jogadores;
}

void nova_rodada_16895603(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao) {
    num_cartas = n_cartas;
    for (int i = 0; i < n_cartas; i++) {
        mao[i] = minha_mao[i];
    }

    manilha_rodada = definir_manilha(carta_virada);
    qsort(mao, num_cartas, sizeof(Carta), comparar_cartas_mao);
}

int apostar_16895603(const int* apostas) {
    double valor_aposta = 0;

    for (int i = 0; i < num_cartas; i++) {
        if (mao[i].valor == manilha_rodada) {
            valor_aposta += 1.0;
        } else if (mao[i].valor == TRES || mao[i].valor == DOIS) {
            valor_aposta += 0.5;
        } else if (mao[i].valor == AS || mao[i].valor == REI) {
            valor_aposta += 0.2;
        }
    }

    aposta_global = round(valor_aposta);

    return round(valor_aposta);
}

int jogar_16895603(const Carta* mesa, const int num_na_mesa, const int vitorias) {
    if (!eh_possivel_ganhar(mesa, num_na_mesa) || vitorias >= aposta_global) {
        for (int i = 0; i < num_cartas; i++) {
            if (!carta_foi_usada(mao[i])) {
                mao[i] = USADA;
                return i;
            }
        }
    }

    for (int i = num_cartas - 1; i >= 0; i--) {
        if (mao[i].valor >= 0) {
            if (!carta_foi_usada(mao[i])) {
                mao[i] = USADA;
                return i;
            }
        }
    }
}