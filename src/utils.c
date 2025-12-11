#include <stdio.h>
#include "utils.h"

/**
 * Lê um inteiro do teclado garantindo que está dentro do intervalo [min, max].
 * Repete a leitura até ser válido.
 */
int lerInteiroNoIntervalo(int min, int max) {
    int valor;
    int resultado_scan;
    
    while (1) {

        // Pede um valor dentro do intervalo
        printf("Digite um valor entre %d e %d: ", min, max);

        // Tenta ler um número inteiro
        resultado_scan = scanf("%d", &valor);

        // Limpa caracteres restantes do buffer (como o '\n')
        limparBufferEntrada();
        
        // Se o scanf falhou (digitou letra por exemplo)
        if (resultado_scan != 1) {
            printf("Valor invalido! Digite apenas numeros inteiros.\n");
            continue; // volta para tentar novamente
        }
        
        // Verifica se está dentro do intervalo
        if (valor < min || valor > max) {
            printf("Valor fora do intervalo permitido! Tente novamente.\n");
            continue;
        }
        
        // Se tudo estiver certo, devolve o valor
        return valor;
    }
}


/**
 * Pausa a execução até o usuário pressionar ENTER.
 * Usado para dar tempo de leitura entre telas/menus.
 */
void pausar(void) {
    printf("Pressione ENTER para continuar...");
    limparBufferEntrada();  // Espera o ENTER
}


/**
 * Limpa o buffer de entrada, descartando caracteres até '\n'
 * Evita que ENTERs acumulados causem pulos na leitura.
 */
void limparBufferEntrada(void) {
    int c;

    // Lê todos os caracteres restantes até achar um '\n' (ENTER)
    while ((c = getchar()) != '\n' && c != EOF) {
        // descartando o que sobrou no buffer
    }
}

