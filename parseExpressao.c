/*
file: parseExpressao.c
Implementação das funções de análise e interpretação de expressões.
*/

#include "assinatura.h"
#include <ctype.h>

Expressao parseExpressao(const char* expressao) {
    Expressao expressao_linha;
    expressao_linha.tamanho = 0;
    int posicao = 0;

    // Percorre a expressão caractere por caractere até o final da string ou até quebra de linha
    while (expressao[posicao] != '\0' && expressao[posicao] != '\n') {

        // Ignorar espaços em branco
        if (isspace(expressao[posicao])) {
            posicao++;
            continue;
        }

        // Instanciar um token vazio e repassar para a máquina de estados processar o token
        Token tokenAtual;
        estadoInicial(expressao, &posicao, &tokenAtual);

        // Guardar o token processado na expressão se houver espaço
        if (expressao_linha.tamanho < MAX_TOKEN_POR_EXPRESSAO) {
            expressao_linha.tokens[expressao_linha.tamanho++] = tokenAtual;
            expressao_linha.tamanho++;
        } else {
            // Caso a expressão exceda o número máximo de tokens, pode-se optar por tratar o erro ou simplesmente ignorar os tokens adicionais
            // TO DO criar exceção para tratar isso
            break;
        }
    }

    // Adicionar um token de fim de expressão para indicar o término da análise
    if (expressao_linha.tamanho < MAX_TOKEN_POR_EXPRESSAO) {
        Token tokenFim;
        tokenFim.tipo = TOKEN_FIM;
        strcpy(tokenFim.valor, "EOF");
        expressao_linha.tokens[expressao_linha.tamanho] = tokenFim;
        expressao_linha.tamanho++;
    }

    return expressao_linha;
}
