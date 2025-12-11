#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "ranking.h"
#include "utils.h"

#define LINHAS_TAB 4
#define COLUNAS_TAB 4
#define ARQUIVO_RANKING "data/ranking.txt"

void mostrarMenuInicial(void); // mostra as acoes que podem ser executadas pelo usuario
void executarOpcaoJogador(void); // coleta os dados do usuario, carrega o tabuleiro, e grava a nova jogada realizada pelo usuario
void executarMostrarRanking(void); // chma a funcao que guarda o ranking e mostra para o usuario

int main(){
    int opcao;

    // para embaralhar cartas de forma diferente a cada execucao
    srand((unsigned) time(NULL));


    do{
        mostrarMenuInicial();
        opcao = lerInteiroNoIntervalo(0, 2); // do utils.h

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

void mostrarMenuInicial(void){ 
    printf("===== JOGO DA MEMORIA =====\n");
    printf("1 - Jogar\n");
    printf("2 - Ver Ranking\n");
    printf("0 - Sair\n");
    printf("===========================\n");
}
void executarOpcaoJogador(void) {
    char nome[50];
    int pontuacao = 0;
    int linha1, linha2, coluna1, coluna2;
    int qtd = 0;

    printf("Qual eh o seu nome? ");
    if (fgets(nome, sizeof(nome), stdin) != NULL) {
        size_t len = strlen(nome);
        if (len > 0 && nome[len - 1] == '\n') {
            nome[len - 1] = '\0'; // tirando o \n do final, senao fica feio no printf dps
        }
    }

    // cria o tabuleiro uma vez so. se der ruim aq o jogo nem comeca
    Carta *tabuleiro = criarTabuleiro(LINHAS_TAB, COLUNAS_TAB);
    if (tabuleiro == NULL) {
        printf("Erro ao criar tabuleiro.\n");
        return;
    }

    // inicializa as cartas e embaralha tudo
    inicializarCartas(tabuleiro, LINHAS_TAB, COLUNAS_TAB);
    embaralharCartas(tabuleiro, LINHAS_TAB * COLUNAS_TAB);

    // loop principal do jogo, vai rodando ate todas as cartas serem encontradas
    while (!todasCartasEncontradas(tabuleiro, LINHAS_TAB, COLUNAS_TAB)) {

        exibirTabuleiro(tabuleiro, LINHAS_TAB, COLUNAS_TAB, 0);

        printf("Escolha a primeira carta (linha): ");
        linha1 = lerInteiroNoIntervalo(0, LINHAS_TAB - 1);

        printf("Escolha a primeira carta (coluna): ");
        coluna1 = lerInteiroNoIntervalo(0, COLUNAS_TAB - 1);

        printf("Escolha a segunda carta (linha): ");
        linha2 = lerInteiroNoIntervalo(0, LINHAS_TAB - 1);

        printf("Escolha a segunda carta (coluna): ");
        coluna2 = lerInteiroNoIntervalo(0, COLUNAS_TAB - 1);

        int resultado = realizarJogada(
            tabuleiro,
            LINHAS_TAB,
            COLUNAS_TAB,
            linha1, coluna1,
            linha2, coluna2
        );

        if (resultado == -1) {
            printf("Jogada invalida, tenta dnv ai.\n");
            pausar();
            continue;
        }

        exibirTabuleiro(tabuleiro, LINHAS_TAB, COLUNAS_TAB, 0);

        if (resultado == 1) {
            printf("ACERTOU!\n");
            pontuacao += 10; // somar a pontuacao
        } else { // resultado == 0
            printf("ERROU!\n");
            pontuacao -= 2;
            if (pontuacao < 0) {
                pontuacao = 0; // nao deixa a pontuacao ficar negativa, fica estranho
            }
        }

        pausar(); // pausa so pra pessoa ver as cartas e nao sumir do nada
        esconderCartasReveladasNaoEncontradas(tabuleiro, LINHAS_TAB, COLUNAS_TAB); // esconde as cartas que nao foram encotradas
    }

    printf("Fim de jogo, %s! Sua pontuacao final foi: %d.\n", nome, pontuacao);

    // monta o jogador pra mandar pro ranking
    Jogador novo;
    strncpy(novo.nome, nome, sizeof(novo.nome));
    novo.nome[sizeof(novo.nome) - 1] = '\0'; // so garantindo que termina certinho a string
    novo.pontos = pontuacao;

    // carrega o ranking do arquivo (se n tiver, volta NULL e qtd = 0)
    Jogador *ranking = carregarRanking(ARQUIVO_RANKING, &qtd);

    if (!atualizarRanking(&ranking, &qtd, novo)) {
        printf("ERRO AO ATUALIZAR RANKING.\n");
    } else {
        if (!salvarRanking(ARQUIVO_RANKING, ranking, qtd)) {
            printf("ERRO AO SALVAR O RANKING!\n");
        } else {
            printf("Ranking atualizado com sucesso :)\n");
        }
    }

    free(ranking);             // libera a memoria do ranking, senao vaza ram aq
    liberarTabuleiro(tabuleiro); // libera a memoria do tabuleiro tmb, senao da leak
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

    pausar();
}
