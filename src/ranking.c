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
        contador++;    
    }

    rewind(arquivo);

    Jogador *jogadores = malloc(contador *sizeof(Jogador));
    while (fscanf(file, " %49s %d", jogadores[i].nome, &jogadores[i].pontos) == 2) {
        i++;
    }

    fclose(file);
    *qtd = contador;
    return jogadores;
}

