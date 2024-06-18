#include "calculadora.h"
#include <stdio.h>
#include <string.h>

// Função para executar um teste
void run_test(char infix[], char expected_description[]) {
    Expressao exp;
    strcpy(exp.infix, infix);
    
    // Converter para postfix
    infix_to_postfix(exp.infix, exp.postfix);
    
    // Avaliar e mostrar expressões e resultados
    printf("Expressão infix: %s\n", exp.infix);
    printf("Expressão postfix: %s\n", exp.postfix);
    
    // Avaliar e mostrar resultado
    exp.valor = evaluate_postfix(exp.postfix);
    printf("Resultado: %.2lf\n", exp.valor);
    printf("Aproximadamente: %s\n\n", expected_description);
}

int main() {
    // Teste 6
    run_test("2 3 + l 5 /", "Aprox. 0.14");

    // Teste 7
    run_test("10 l 3 ^ 2 +", "3");

    // Teste 8
    run_test("45 60 + 30 c *", "Aprox. 90.93");

    // Teste 9
    run_test("0.5 45 s 2 ^ +", "1");

    return 0;
}