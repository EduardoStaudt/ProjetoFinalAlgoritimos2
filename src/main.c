#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "game.h"
// #include "ranking.h"
// #include "utils.h"

#define LINHAS_TAB 4
#define COLUNAS_TAB 4
#define ARQUIVO_RANKING "data/ranking.txt""

void mostrarMenuInicial(void){ // FUNCAO DE MOSTRAR MENU
    printf("===== JOGO DA MEMORIA =====\n");
    printf("1 - Jogar\n");
    printf("2 - Ver Ranking\n");
    printf("0 - Sair\n");
    printf("===========================\n");
}
void executarOpcaoJogador(void){ // 
    printf("Qual eh o seu Nome? ");
    // 1. Perguntar nome do jogador
    // 2. Criar tabuleiro com criarTabuleiro(...)
    // 3. Loop de jogadas chamando funcoes de game.c
    // 4. Calcular pontuacao
    // 5. Atualizar ranking chamando funcoes de ranking.c
}
void executarMostrarRanking(void){
    // 1. Carregar ranking do arquivo
    // 2. Mostrar ranking na tela
    printf("");
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
