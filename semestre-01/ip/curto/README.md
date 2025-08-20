# Curto

## Descrição
**Curto** é um projeto didático desenvolvido para ensinar conceitos fundamentais de programação em C. O programa simula um jogo de cartas simples, abordando tópicos como estruturas, enumerações, ponteiros, funções e modularização.



## Funcionalidades
- **Cartas**: Cada carta possui um **naipe** (`OUROS`, `ESPADAS`, `COPAS`, `PAUS`) e um **valor** (`4-7`, `DAMA`, `VALETE`, `REI`, `AS`, `2`, `3`).
- **Baralho**: Um baralho padrão é inicializado e embaralhado, contendo todas as combinações de cartas.
- **Jogadores**: Suporte para múltiplos jogadores, cada um com estratégias de aposta e jogada.
- **Rodadas**: Gerenciamento de rodadas, incluindo distribuição de cartas, apostas e resolução de mãos.
- **Jogo Completo**: Coordenação de rodadas, cálculo de penalidades e determinação do vencedor.

## Estrutura do Projeto
- **Arquivos principais**:
  - `main.c`: Ponto de entrada do programa.
  - `baralho.c`: Gerenciamento do baralho.
  - `rodada.c`: Lógica das rodadas.
  - `mao.c`: Resolução de mãos.
  - `jogo.c`: Controle geral do jogo.
- **Jogadores**:
  - Estratégias implementadas na pasta `jogadores/`

## Jogadores
Cada jogador deve implementar as seguintes funções para definir seu comportamento no jogo:

- **`inicializar_jogador`**: Configura o estado inicial do jogador, como nome e estratégia.
  - **Parâmetros**:
    - `meu_id`: Identificador único do jogador.
    - `total_jogadores`: Número total de jogadores na partida.

- **`nova_rodada`**: Prepara o jogador para uma nova rodada.
  - **Parâmetros**:
    - `rodada`: Número da rodada atual.
    - `carta_virada`: Carta que define a manilha da rodada.
    - `n_cartas`: Número de cartas na mão do jogador.
    - `minha_mao`: Vetor contendo as cartas na mão do jogador.

- **`apostar`**: Define o valor da aposta do jogador com base em sua estratégia e nas cartas recebidas.
  - **Parâmetros**:
    - `apostas`: Vetor contendo as apostas dos outros jogadores.

- **`jogar_carta`**: Escolhe qual carta jogar durante a rodada.
  - **Parâmetros**:
    - `mesa`: Vetor contendo as cartas jogadas na mesa até o momento.
    - `num_na_mesa`: Número de cartas atualmente na mesa.

- **`nome`**: Retorna o nome do jogador para exibição no jogo.
  - **Parâmetros**:
    - Nenhum.

## Regras do Jogo

1. **Objetivo**: O objetivo do jogo é terminar com a menor penalidade possível, apostando corretamente e jogando cartas estrategicamente.

2. **Manilha**: A cada rodada, uma carta é virada para definir a manilha. A manilha é a carta imediatamente superior à carta virada, seguindo a ordem dos valores.

3. **Rodadas**:
   - Cada jogador recebe um conjunto de cartas no início da rodada.
   - Os jogadores fazem suas apostas, indicando quantas rodadas acreditam que podem vencer.
   - Os jogadores jogam uma carta por vez, seguindo a ordem da mesa.
   - A carta mais forte, considerando o valor e a manilha, vence a rodada.

4. **Pontuação**:
   - Um jogador recebe penalidades se vencer mais ou menos rodadas do que apostou.
   - Se vencer exatamente o número de rodadas apostadas, o jogador não recebe penalidades.

5. **Fim do Jogo**: O jogo termina após um número pré-determinado de rodadas. O jogador com a menor penalidade total é declarado vencedor.

## Compilação e Execução

### Compilação
Para compilar o programa principal, execute:
```bash
make main
```

### Execução
Para executar o programa, utilize:
```bash
./main
```

## Licença
Este projeto é livre para uso acadêmico e didático. Sinta-se à vontade para modificá-lo e adaptá-lo às suas necessidades.
