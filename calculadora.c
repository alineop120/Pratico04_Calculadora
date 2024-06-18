#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>  // Para isdigit

typedef struct {
    double items[100];
    int top;
} Stack;

void push(Stack *s, double value) {
    if (s->top == 99) {
        printf("Erro: Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
    s->top++;
    s->items[s->top] = value;
}

double pop(Stack *s) {
    if (s->top == -1) {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
    double value = s->items[s->top];
    s->top--;
    return value;
}

double peek(Stack *s) {
    if (s->top == -1) {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top];
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^'
            || c == 's' || c == 'c' || c == 't' || c == 'l');
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^' || c == 's' || c == 'c' || c == 't' || c == 'l') return 3;
    else return 0;
}

void infix_to_postfix(char infix[], char postfix[]) {
    Stack stack;
    stack.top = -1;
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i]) || infix[i] == '.') {
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            push(&stack, infix[i]);
        } else if (infix[i] == ')') {
            while (stack.top != -1 && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            pop(&stack);
        } else if (is_operator(infix[i])) {
            while (stack.top != -1 && precedence(peek(&stack)) >= precedence(infix[i])) {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            push(&stack, infix[i]);
        }
        i++;
    }
    while (stack.top != -1) {
        postfix[j++] = pop(&stack);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

double evaluate_postfix(char postfix[]) {
    Stack stack;
    stack.top = -1;
    int i = 0;
    double operand1, operand2, result;
    char *token;
    char delimiter[] = " ";
    
    token = strtok(postfix, delimiter);
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&stack, atof(token));
        } else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '^') {
            operand2 = pop(&stack);
            operand1 = pop(&stack);
            switch (token[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                case '^':
                    result = pow(operand1, operand2);
                    break;
                default:
                    break;
            }
            push(&stack, result);
        } else if (token[0] == 's' || token[0] == 'c' || token[0] == 't' || token[0] == 'l') {
            operand1 = pop(&stack);
            switch (token[0]) {
                case 's':
                    result = sin(operand1 * M_PI / 180.0); // Converte para radianos
                    break;
                case 'c':
                    result = cos(operand1 * M_PI / 180.0); // Converte para radianos
                    break;
                case 't':
                    result = tan(operand1 * M_PI / 180.0); // Converte para radianos
                    break;
                case 'l':
                    result = log(operand1); // Logaritmo na base natural (ln)
                    break;
                default:
                    break;
            }
            push(&stack, result);
        }
        token = strtok(NULL, delimiter);
    }
    return pop(&stack);
}
