// funcoes e structs do ranking
#ifndef RANKING_H
#define RANKING_H

typedef struct{
    char nome[50];
    int pontos;
}Jogador;

Jogador* carregarRanking(const char *arquivo, int *qtd);

int salvarRanking(const char *arquivo, const Jogador *ranking, int qtd);

int atualizarRanking(Jogador **ranking, int *qtd, Jogador novoJogador);

void ordenarRanking(Jogador *ranking, int qtd);

void exibirRanking(const Jogador *ranking, int qtd);

#endif

