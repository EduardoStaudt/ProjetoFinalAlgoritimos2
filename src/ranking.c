#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

Jogador* carregarRanking(const char *arquivo, int *qtd) {
    *qtd = 0;

    FILE *f = fopen(arquivo, "r");
    if (!f) {
        // primeira vez rodando, sem arquivo ainda
        return NULL;
    }

    char buffer[128];
    int count = 0;

    // conta quantas linhas "validas" tem
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        if (buffer[0] != '\n' && buffer[0] != '\0') {
            count++;
        }
    }

    if (count == 0) {
        fclose(f);
        return NULL;
    }

    Jogador *ranking = (Jogador*) malloc(count * sizeof(Jogador));
    if (!ranking) {
        fclose(f);
        return NULL;
    }

    rewind(f);
    int i = 0;
    while (i < count && fgets(buffer, sizeof(buffer), f) != NULL) {
        char nome[50];
        int pontos;

        if (sscanf(buffer, "%49[^;];%d", nome, &pontos) == 2) {
            strncpy(ranking[i].nome, nome, sizeof(ranking[i].nome));
            ranking[i].nome[sizeof(ranking[i].nome) - 1] = '\0';
            ranking[i].pontos = pontos;
            i++;
        }
    }

    fclose(f);
    *qtd = i;

    if (*qtd == 0) {
        free(ranking);
        return NULL;
    }

    return ranking;
}

int salvarRanking(const char *arquivo, const Jogador *ranking, int qtd) {
    FILE *f = fopen(arquivo, "w");
    if (!f) return 0;

    for (int i = 0; i < qtd; i++) {
        fprintf(f, "%s;%d\n", ranking[i].nome, ranking[i].pontos);
    }

    fclose(f);
    return 1;
}

void ordenarRanking(Jogador *ranking, int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - 1 - i; j++) {
            if (ranking[j].pontos < ranking[j + 1].pontos) {
                Jogador tmp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = tmp;
            }
        }
    }
}

int atualizarRanking(Jogador **ranking, int *qtd, Jogador novoJogador) {
    if (*ranking == NULL || *qtd == 0) {
        Jogador *novo = (Jogador*) malloc(sizeof(Jogador));
        if (!novo) return 0;

        novo[0] = novoJogador;
        *ranking = novo;
        *qtd = 1;
        return 1;
    } else {
        int novaQtd = *qtd + 1;
        Jogador *novo = (Jogador*) realloc(*ranking, novaQtd * sizeof(Jogador));
        if (!novo) return 0;

        novo[novaQtd - 1] = novoJogador;
        *ranking = novo;
        *qtd = novaQtd;
        ordenarRanking(*ranking, *qtd);
        return 1;
    }
}

void exibirRanking(const Jogador *ranking, int qtd) {
    if (!ranking || qtd == 0) {
        printf("Ainda nao ha jogadores no ranking.\n");
        return;
    }

    printf("\n===== RANKING =====\n");
    printf("%-4s %-20s %-6s\n", "Pos", "Nome", "Pts");

    for (int i = 0; i < qtd; i++) {
        printf("%-4d %-20s %-6d\n", i + 1, ranking[i].nome, ranking[i].pontos);
    }

    printf("\n");
}