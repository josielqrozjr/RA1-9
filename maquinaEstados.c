/*
file: maquinaEstados.c
Implementação da máquina de estados da aplicação.
*/

#include "assinatura.h"
#include <ctype.h>
#include <string.h>

// Função para auxiliar na identificação de operadores
static bool isOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}

void estadoInicial(const char* expressao, int *posicao, Token *tokenAtual) {
    char c = expressao[*posicao];

    if (isdigit(c)) {
        estadoNumero(expressao, posicao, tokenAtual);
    }
    else if (isOperador(c)) {
        estadoOperador(expressao, posicao, tokenAtual);
    }
    else if (c == '(') {
        tokenAtual->tipo = TOKEN_PAREN_ABERTURA;
        strcpy(tokenAtual->valor, "(");
        (*posicao)++;
    }
    else if (c == ')') {
        tokenAtual->tipo = TOKEN_PAREN_FECHADO;
        strcpy(tokenAtual->valor, ")");
        (*posicao)++;
    }
    else if (isupper(c)) {
        estadoAlfa(expressao, posicao, tokenAtual);
    }
    else {
        // Caso o caractere seja inválido ou não esteja na linguagem
        tokenAtual->tipo = TOKEN_ERRO;
        tokenAtual->valor[0] = c;
        tokenAtual->valor[1] = '\0';
        (*posicao)++;
    }
}

