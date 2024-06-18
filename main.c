#include <stdio.h>
#include <stdlib.h>
#include "calculadora.h"
#include <math.h>

int main() {
    char posFixa[] = "2 3 + log 5 /";
    
    // Convertendo para a forma infixa
    char *inFixa = getFormaInFixa(posFixa);
    printf("Forma inFixa: %s\n", inFixa);
    free(inFixa);  // Liberando a memória alocada pelo malloc em getFormaInFixa

    // Calculando o valor da expressão
    float valor = getValor(posFixa);
    printf("Valor da expressao: %.2f\n", valor);
    
    return 0;
}




