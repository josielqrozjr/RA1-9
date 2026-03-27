/*
file: assinatura.h
Cabeçalhos das funções utilizadas na aplicação.
*/

#ifndef ASSINATURA_H
#define ASSINATURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TOKEN_TAM 64
#define MAX_TOKEN_POR_EXPRESSAO 256

// Definindo os tipos de tokens existentes no conjunto
typedef enum {
    TOKEN_NUMERO,           // Números inteiros ou decimais
    TOKEN_OPERADOR,         // Operadores aritméticos: +, -, *, /, //, %, ^
    TOKEN_PAREN_ABERTURA,   // Parêntese de abertura: (
    TOKEN_PAREN_FECHADO,    // Parêntese de fechamento: )
    TOKEN_KEYWORD_RES,      // Palavra-chave: RES
    TOKEN_KEYWORD_MEM,      // Palavra-chave: MEM
    TOKEN_ALFA,             // Letras maiúsculas do alfabeto
    TOKEN_ERRO,             // Token inválido
    TOKEN_FIM               // Fim da expressão
} TokenTipo;

// Estrutura para representar um token
typedef struct {
    TokenTipo tipo;             // Tipo do token
    char valor[MAX_TOKEN_TAM];  // Valor do token
} Token;

// Estrutura para representar uma expressão/vetor de tokens
typedef struct {
    Token tokens[MAX_TOKEN_POR_EXPRESSAO];  // Vetor de tokens
    int tamanho;                            // Número de tokens na expressão
} Expressao;

// Assinaturas das funções
// Máquina de estados para análise léxica (maquinaEstados.c)
void estadoInicial(const char* expressao, int *posicao, Token *tokenAtual);
void estadoNumero(const char* expressao, int *posicao, Token *tokenAtual);
void estadoOperador(const char* expressao, int *posicao, Token *tokenAtual);
void estadoAlfa(const char* expressao, int *posicao, Token *tokenAtual);

// Função para tokenizar a expressão (parseExpressao.c)
Expressao parseExpressao(const char* expressao);

// Função para ler o arquivo de entrada (lerArquivo.c)
int lerArquivo(const char *nomeArquivo, char expressoes[][MAX_TOKEN_POR_EXPRESSAO], int *quantExpressoes);

// Função para executar 

#endif // ASSINATURA_H