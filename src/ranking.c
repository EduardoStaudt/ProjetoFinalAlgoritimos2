// acoes relacionadas aos arquivo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

Jogador* carregarRanking(const char *arquivo, int *qtd) {
    FILE *file;
    char linhas[100];
    int contador = 0, i = 0;

    file = fopen(arquivo, "r");
    
    if(file == NULL){
        *qtd = 0;
        return NULL;
    }

    while(fgets(linhas, sizeof(linhas), file) != NULL) { 
        if (strlen(linhas) > 1){
        contador++;    
        }
    }

    rewind(file);

    Jogador *ranking = malloc(contador *sizeof(Jogador));

    if(ranking == NULL && contador > 0){
        fclose(file);
        *qtd = 0;
        return NULL;
    }
    
    while (i < contador && fscanf(file, " %49s %d", ranking[i].nome, &ranking[i].pontos) == 2) {
        i++;
    }

    fclose(file);
    *qtd = i;
    return ranking;
}

int salvarRanking(const char *arquivo, const Jogador *ranking, int qtd){
    FILE *file;
    
    file = fopen(arquivo, "w");
    
    if(file == NULL){
        return 0;
    }

    for (int i = 0; i < qtd; i++) {
        fprintf(file, "%s %d\n", ranking[i].nome, ranking[i].pontos);
    }
    
    fclose(file);
    return 1;
}

int atualizarRanking(Jogador **ranking, int *qtd, Jogador novoJogador) {
    Jogador *upd = realloc(*ranking, (*qtd+1) * sizeof(Jogador));

        if(upd == NULL){
        return 0;
    }

    *ranking = upd;
    *(*ranking + *qtd) = novoJogador;
    (*qtd)++;

    ordenarRanking(*ranking, *qtd);
    
    return 1;
}

void ordenarRanking(Jogador *ranking, int qtd){
for (int i = 1; i < qtd; i++) {
        Jogador jogadorAtual = ranking[i];
        
        int j = i - 1;
        
        while (j >= 0 && ranking[j].pontos < jogadorAtual.pontos) {
            ranking[j + 1] = ranking[j];
            j--;
        }
        ranking[j + 1] = jogadorAtual;
    }
}

void exibirRanking(const Jogador *ranking, int qtd) {
    printf("\nRANKING\n");
    
    if (qtd == 0) {
        printf("Ranking vazio.\n");
        return;
    }
    
    for (int i = 0; i < qtd; i++) {
        printf("Pos. %d: Nome: %s Pontos: %d\n", i + 1, ranking[i].nome, ranking[i].pontos);
    }
}

