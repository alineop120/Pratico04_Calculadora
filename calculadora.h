#ifndef CALCULADORA_H
#define CALCULADORA_H

// Definição do TAD Expressão
typedef struct {
    char infix[100]; // Expressão na notação infix
    char postfix[100]; // Expressão na notação postfix
    double valor; // Valor da expressão
} Expressao;

// Protótipos das funções
void infix_to_postfix(char infix[], char postfix[]);
double evaluate_postfix(char postfix[]);

#endif /* CALCULADORA_H */