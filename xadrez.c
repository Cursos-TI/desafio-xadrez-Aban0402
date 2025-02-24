#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABULEIRO 8

#define VAZIO 0
#define PEAO 1
#define TORRE 2
#define CAVALO 3
#define BISPO 4
#define RAINHA 5
#define REI 6

#define BRANCO 0
#define PRETO 1

int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

void inicializarTabuleiro() {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VAZIO;
        }
    }

    tabuleiro[0][0] = tabuleiro[0][7] = TORRE;
    tabuleiro[0][1] = tabuleiro[0][6] = CAVALO;
    tabuleiro[0][2] = tabuleiro[0][5] = BISPO;
    tabuleiro[0][3] = RAINHA;
    tabuleiro[0][4] = REI;
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        tabuleiro[1][i] = PEAO;
    }

    tabuleiro[7][0] = tabuleiro[7][7] = TORRE;
    tabuleiro[7][1] = tabuleiro[7][6] = CAVALO;
    tabuleiro[7][2] = tabuleiro[7][5] = BISPO;
    tabuleiro[7][3] = RAINHA;
    tabuleiro[7][4] = REI;
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        tabuleiro[6][i] = PEAO;
    }
}

void imprimirTabuleiro() {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            switch (tabuleiro[i][j]) {
                case VAZIO: printf(". "); break;
                case PEAO: printf("P "); break;
                case TORRE: printf("T "); break;
                case CAVALO: printf("C "); break;
                case BISPO: printf("B "); break;
                case RAINHA: printf("Q "); break;
                case REI: printf("K "); break;
            }
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n");
}

void converterCoordenadas(char *movimento, int *linha, int *coluna) {
    *coluna = movimento[0] - 'a'; 
    *linha = 8 - (movimento[1] - '0'); 
}

int processarMovimento(char *origemStr, char *destinoStr) {
    int linhaOrigem, colunaOrigem, linhaDestino, colunaDestino;

    converterCoordenadas(origemStr, &linhaOrigem, &colunaOrigem);
    converterCoordenadas(destinoStr, &linhaDestino, &colunaDestino);

    if (tabuleiro[linhaOrigem][colunaOrigem] == VAZIO) {
        printf("Movimento inválido: não há peça na posição de origem.\n");
        return 0;
    }

    tabuleiro[linhaDestino][colunaDestino] = tabuleiro[linhaOrigem][colunaOrigem];
    tabuleiro[linhaOrigem][colunaOrigem] = VAZIO;

    return 1;
}

void voidRecursiveLoop(int jogador) {
    imprimirTabuleiro();

    char origem[3], destino[3];
    printf("Jogador %d, faça sua jogada (ex: e2 e4): ", jogador + 1);
    scanf("%s %s", origem, destino);

    if (processarMovimento(origem, destino)) {
        int proximoJogador = (jogador == BRANCO) ? PRETO : BRANCO;

        voidRecursiveLoop(proximoJogador);
    } else {
        voidRecursiveLoop(jogador);
    }
}

int main() {
    inicializarTabuleiro();
    voidRecursiveLoop(BRANCO); 
    return 0;
}
