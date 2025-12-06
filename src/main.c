#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "ranking.h"
#include "utils.h"

#define LINHAS_TAB 4
#define COLUNAS_TAB 4
#define ARQUIVO_RANKING "data/ranking.txt"

void mostrarMenuInicial(void){ // FUNCAO DE MOSTRAR MENU
    printf("===== JOGO DA MEMORIA =====\n");
    printf("1 - Jogar\n");
    printf("2 - Ver Ranking\n");
    printf("0 - Sair\n");
    printf("===========================\n");
}
void executarOpcaoJogador(void){ // 
    char nome[50];
    int pontuacao = 0, linha1, linha2, coluna1, coluna2, qtd = 0;

    printf("Qual eh o seu Nome? ");
    fgets(nome, sizeof(nome), stdin); // para tirar o \n se tiver

    Carta *tabuleiro = NULL;

    tabuleiro = criarTabuleiro(LINHAS_TAB, COLUNAS_TAB);
    if (tabuleiro == NULL){
        printf("Erro ao ccriar tabuleiro.\n");
        return;
    }

    inicializarCartas(tabuleiro, LINHAS_TAB, COLUNAS_TAB);
    embaralharCartas(tabuleiro, LINHAS_TAB, COLUNAS_TAB);
    
    while (!todasCartasEncontradas(tabuleiro, LINHAS_TAB, COLUNAS_TAB)){
        printf("Escolha a primeira carta(linha e coluna): \n");
        linha1 = lerInteiroNoIntervalo(0, LINHAS_TAB - 1);
        coluna1 = lerInteiroNoIntervalo(0, COLUNAS_TAB - 1);

        printf("Escolha a segunda carta(linha e coluna): \n");
        linha2 = lerInteiroNoIntervalo(0, LINHAS_TAB - 1);
        coluna2 = lerInteiroNoIntervalo(0, COLUNAS_TAB - 1);

        int acertou = realizarJogada(tabuleiro, LINHAS_TAB, COLUNAS_TAB, linha1, coluna1, linha2, coluna2);

        if (acertou){
            printf("ACERTOU!\n");
            pontuacao += 10;
        } else {
            printf("ERROU!\n");
            pontuacao -= 2;
        }
    }

    printf("Fim de Jogo, %s! Sua pontucao final foi: %d.\n", nome, pontuacao);

    Jogador novo; // Struct
    strncpy(novo.nome, nome, sizeof(novo.nome));
    novo.nome[sizeof(novo.nome) - 1] = '\0'; // para a string sempre tereum fim
    novo.pontos = pontuacao;
    Jogador *ranking = carregarRanking(ARQUIVO_RANKING, ranking, qtd);

    if (!atualizarRanking(&ranking, &qtd, novo)){
        printf("ERRO AO ATUALIZAR RANKING.\n");
    }else{
        if(!salvarRanking(ARQUIVO_RANKING, ranking, qtd)){
            printf("ERRO AO SALVAR O RANKING!\n");
        }
    }

    free(ranking); // Liberando a memoriaa apos o uso
    limparTabuleiro(tabuleiro);
}
void executarMostrarRanking(void){
    int qtd = 0;
    Jogador *ranking = carregarRanking(ARQUIVO_RANKING, &qtd);

    if(ranking  == NULL || qtd == 0){
        printf("O RANKING AINDA NAO POSSUI RESULTADOS!\n");
    }else{
        exibirRanking(ranking, qtd);
        free(ranking); // memoria limpada
    }
}



int main(){
    int opcao;

    do{
        mostrarMenuInicial();
        opcao = LerInteiroNoIntervalo(0, 2);

        switch(opcao){
            case 1:
                executarOpcaoJogador();
                break;
            case 2:
                executarMostrarRanking();
                break;
            case 0: 
                printf("Saindo do Jogo...\n");
                printf("===== Obrigado por Jogar! =====\n");
                break;
            default:
                printf("Opcao Invalida.\n");
        }
    }while(opcao != 0);

    return 0;
}
