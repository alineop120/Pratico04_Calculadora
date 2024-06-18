#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct {
    float valores[512];
    int topo;
} Pilha;

void inicializaPilha(Pilha *p) {
    p->topo = -1;
}

void empilha(Pilha *p, float valor) {
    p->valores[++p->topo] = valor;
}

float desempilha(Pilha *p) {
    return p->valores[p->topo--];
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int eOperando(char ch) {
    return isdigit(ch) || ch == '.';
}

int eOperador(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == 's' || ch == 'c' || ch == 'l';
}

int precedencia(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
        case 's':
        case 'c':
        case 'l':
            return 3;
        default:
            return 0;
    }
}

char *getFormaInFixa(char *Str) {
    Pilha pilha;
    inicializaPilha(&pilha);
    int tamanho = strlen(Str);
    char *inFixa = (char *)malloc(tamanho * sizeof(char));
    int j = 0;

    for (int i = 0; i < tamanho; i++) {
        if (eOperando(Str[i])) {
            while (eOperando(Str[i])) {
                inFixa[j++] = Str[i++];
            }
            inFixa[j++] = ' ';
            i--;
        } else if (eOperador(Str[i])) {
            while (!pilhaVazia(&pilha) && precedencia(pilha.valores[pilha.topo]) >= precedencia(Str[i])) {
                inFixa[j++] = pilha.valores[pilha.topo--];
                inFixa[j++] = ' ';
            }
            empilha(&pilha, Str[i]);
        } else if (Str[i] == '(') {
            empilha(&pilha, Str[i]);
        } else if (Str[i] == ')') {
            while (pilha.valores[pilha.topo] != '(') {
                inFixa[j++] = pilha.valores[pilha.topo--];
                inFixa[j++] = ' ';
            }
            pilha.topo--;  // Desempilha '('
        }
    }

    while (!pilhaVazia(&pilha)) {
        inFixa[j++] = pilha.valores[pilha.topo--];
        inFixa[j++] = ' ';
    }

    inFixa[j] = '\0';
    return inFixa;
}

float getValor(char *Str) {
    Pilha pilha;
    inicializaPilha(&pilha);
    int tamanho = strlen(Str);

    for (int i = 0; i < tamanho; i++) {
        if (eOperando(Str[i])) {
            char numero[20];
            int j = 0;
            while (eOperando(Str[i])) {
                numero[j++] = Str[i++];
            }
            numero[j] = '\0';
            float valor = atof(numero);
            empilha(&pilha, valor);
            i--;
        } else if (eOperador(Str[i])) {
            float op2, op1, resultado;

            switch (Str[i]) {
                case '+':
                    op2 = desempilha(&pilha);
                    op1 = desempilha(&pilha);
                    resultado = op1 + op2;
                    empilha(&pilha, resultado);
                    break;
                case '-':
                    op2 = desempilha(&pilha);
                    op1 = desempilha(&pilha);
                    resultado = op1 - op2;
                    empilha(&pilha, resultado);
                    break;
                case '*':
                    op2 = desempilha(&pilha);
                    op1 = desempilha(&pilha);
                    resultado = op1 * op2;
                    empilha(&pilha, resultado);
                    break;
                case '/':
                    op2 = desempilha(&pilha);
                    op1 = desempilha(&pilha);
                    resultado = op1 / op2;
                    empilha(&pilha, resultado);
                    break;
                case '^':
                    op2 = desempilha(&pilha);
                    op1 = desempilha(&pilha);
                    resultado = pow(op1, op2);
                    empilha(&pilha, resultado);
                    break;
                case 's':
                    op1 = desempilha(&pilha);
                    resultado = sin(op1);
                    empilha(&pilha, resultado);
                    break;
                case 'c':
                    op1 = desempilha(&pilha);
                    resultado = cos(op1);
                    empilha(&pilha, resultado);
                    break;
                case 'l':
                    op1 = desempilha(&pilha);
                    resultado = log(op1);
                    empilha(&pilha, resultado);
                    break;
            }
        }
    }

    return desempilha(&pilha);
}
