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

// Função para processar o estado inicial da máquina de estados
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

// Função para processar o estado de números
void estadoNumero(const char* expressao, int *posicao, Token *tokenAtual) {
    int indice = 0;
    tokenAtual->tipo = TOKEN_NUMERO;

    // Leitura dos dígitos do número e possível ponto decimal
    while (expressao[*posicao] != '\0' && (isdigit(expressao[*posicao]) || expressao[*posicao] == '.' )) {
        if (indice < MAX_TOKEN_TAM - 1) {
            tokenAtual->valor[indice++] = expressao[*posicao];
        }
        (*posicao)++;
    }
    tokenAtual->valor[indice] = '\0';
}

// Função para processar o estado de operadores
void estadoOperador(const char* expressao, int *posicao, Token *tokenAtual) {
    int indice = 0;
    tokenAtual->tipo = TOKEN_OPERADOR;
    tokenAtual->valor[indice++] = expressao[*posicao];
    (*posicao)++;

    // Verificação para operadores de dois caracteres de divisão inteira (//)
    if (tokenAtual->valor[0] == '/' && expressao[*posicao] == '/') {
        tokenAtual->valor[indice++] = expressao[*posicao];
        (*posicao)++;
    }
    tokenAtual->valor[indice] = '\0';
}

// Função para processar o estado de letras maiúsculas (alfabeto)
void estadoAlfa(const char* expressao, int *posicao, Token *tokenAtual) {
    int indice = 0;

    // Leitura de letras maiúsculas para formar palavras-chave ou identificadores
    while (expressao[*posicao] != '\0' && isupper(expressao[*posicao])) {
        if (indice < MAX_TOKEN_TAM - 1) {
            tokenAtual->valor[indice++] = expressao[*posicao];
        }
        (*posicao)++;
    }
    tokenAtual->valor[indice] = '\0';

    // Classificação do token como palavra-chave ou alfa
    if (strcmp(tokenAtual->valor, "RES") == 0) { tokenAtual->tipo = TOKEN_KEYWORD_RES; }
    else { tokenAtual->tipo = TOKEN_ALFA; }
}
