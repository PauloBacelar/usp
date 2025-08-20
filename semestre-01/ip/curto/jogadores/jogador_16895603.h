#ifndef BACELAR_H
#define BACELAR_H

#include "../baralho.h"

const char* nome_16895603();
void iniciar_16895603(const int meu_id, const int total_jogadores);
void nova_rodada_16895603(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao);
int apostar_16895603(const int* apostas);
int jogar_16895603(const Carta* mesa, const int num_na_mesa, const int vitorias);
int eh_possivel_ganhar(const Carta* mesa, const int num_na_mesa);
int existe_manilha(Carta* cartas, int qntd_cartas);
int comparar_cartas_mao(const void* a, const void* b);
Carta get_carta_mais_forte(Carta* cartas, int qntd_cartas);
void imprimir_mao();

#endif // BACELAR_H