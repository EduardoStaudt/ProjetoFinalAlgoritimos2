#include <stdio.h>
#include "utils.h"

int lerInteiroNoIntervalo(int min, int max) {
    int valor;
    int resultado_scan;
    
    while (1) {
        printf("Digite um valor entre %d e %d: ", min, max);
        resultado_scan = scanf("%d", &valor);
        
        limparBufferEntrada();
        

        if (resultado_scan != 1) {
            printf("Valor invalido! Digite apenas numeros inteiros.\n");
            continue;
        }
        
 
        if (valor < min || valor > max) {
            printf("Valor fora do intervalo permitido! Tente novamente.\n");
            continue;
        }
        
        return valor;
    }
}

void limparBufferEntrada(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {

    }
}
