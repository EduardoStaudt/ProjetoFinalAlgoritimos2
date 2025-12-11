#ifndef GAME_H
#define GAME_H

typedef struct {
    char simbolo;     // letra que representa o par
    int encontrada;   // 1 se ja foi encontrada
    int revelada;     // 1 se ta virada pra cima agr
} Carta;

Carta* criarTabuleiro(int linhas, int colunas);
void liberarTabuleiro(Carta *tabuleiro);
void inicializarCartas(Carta *tabuleiro, int linhas, int colunas);
void embaralharCartas(Carta *tabuleiro, int tamanho);
void exibirTabuleiro(const Carta *tabuleiro, int linhas, int colunas, int revelarTudo);
int todasCartasEncontradas(const Carta *tabuleiro, int linhas, int colunas);
int realizarJogada(Carta *tabuleiro, int linhas, int colunas,
                   int linha1, int col1, int linha2, int col2);
void esconderCartasReveladasNaoEncontradas(Carta *tabuleiro, int linhas, int colunas);

#endif