#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

static int indiceCarta(int linha, int coluna, int colunas) {
    return linha * colunas + coluna;
}

Carta* criarTabuleiro(int linhas, int colunas) {
    int tamanho = linhas * colunas;
    Carta *tabuleiro = (Carta*) malloc(tamanho * sizeof(Carta));
    if (!tabuleiro) {
        return NULL;
    }
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[i].simbolo = '?';
        tabuleiro[i].encontrada = 0;
        tabuleiro[i].revelada = 0;
    }
    return tabuleiro;
}

void liberarTabuleiro(Carta *tabuleiro) {
    free(tabuleiro);
}

void inicializarCartas(Carta *tabuleiro, int linhas, int colunas) {
    int tamanho = linhas * colunas;
    int numPares = tamanho / 2;
    int idx = 0;

    for (int i = 0; i < numPares; i++) {
        char simbolo = 'A' + (i % 26); // se estourar de Z volta pro comeco
        tabuleiro[idx].simbolo = simbolo;
        tabuleiro[idx].encontrada = 0;
        tabuleiro[idx].revelada = 0;
        idx++;

        tabuleiro[idx].simbolo = simbolo;
        tabuleiro[idx].encontrada = 0;
        tabuleiro[idx].revelada = 0;
        idx++;
    }
}

void embaralharCartas(Carta *tabuleiro, int tamanho) {
    if (tamanho <= 1) return;

    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta temp = tabuleiro[i];
        tabuleiro[i] = tabuleiro[j];
        tabuleiro[j] = temp;
    }
}

void exibirTabuleiro(const Carta *tabuleiro, int linhas, int colunas, int revelarTudo) {
    printf("\n    ");
    for (int c = 0; c < colunas; c++) {
        printf("%d   ", c);
    }
    printf("\n");

    for (int l = 0; l < linhas; l++) {
        printf("%d | ", l);
        for (int c = 0; c < colunas; c++) {
            int idx = indiceCarta(l, c, colunas);
            char ch = 'X';
            if (revelarTudo || tabuleiro[idx].encontrada || tabuleiro[idx].revelada) {
                ch = tabuleiro[idx].simbolo;
            }
            printf("%c   ", ch);
        }
        printf("\n");
    }
    printf("\n");
}

int todasCartasEncontradas(const Carta *tabuleiro, int linhas, int colunas) {
    int tamanho = linhas * colunas;
    for (int i = 0; i < tamanho; i++) {
        if (!tabuleiro[i].encontrada) {
            return 0;
        }
    }
    return 1;
}

int realizarJogada(Carta *tabuleiro, int linhas, int colunas,
                   int linha1, int col1, int linha2, int col2) {

    // confere se ta tudo dentro do tabuleiro
    if (linha1 < 0 || linha1 >= linhas || col1 < 0 || col1 >= colunas ||
        linha2 < 0 || linha2 >= linhas || col2 < 0 || col2 >= colunas) {
        return -1; // coordenada invalida
    }

    int idx1 = indiceCarta(linha1, col1, colunas);
    int idx2 = indiceCarta(linha2, col2, colunas);

    if (idx1 == idx2) {
        return -1; // msm carta, nao vale
    }
    if (tabuleiro[idx1].encontrada || tabuleiro[idx2].encontrada) {
        return -1; // carta ja tinha sido encontrada antes
    }

    tabuleiro[idx1].revelada = 1;
    tabuleiro[idx2].revelada = 1;

    if (tabuleiro[idx1].simbolo == tabuleiro[idx2].simbolo) {
        tabuleiro[idx1].encontrada = 1;
        tabuleiro[idx2].encontrada = 1;
        return 1; // acertou
    } else {
        return 0; // errou, quem chamou decide quando esconder
    }
}

void esconderCartasReveladasNaoEncontradas(Carta *tabuleiro, int linhas, int colunas) {
    int tamanho = linhas * colunas;
    for (int i = 0; i < tamanho; i++) {
        if (!tabuleiro[i].encontrada && tabuleiro[i].revelada) {
            tabuleiro[i].revelada = 0;
        }
    }
}