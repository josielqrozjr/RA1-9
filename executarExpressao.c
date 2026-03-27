/*
file: executarExpressao.c
Implementação das funções de execução de expressões.
*/

#include "assinatura.h"

// Função auxiliar para inserir uma variável na tabela de símbolos
static void registrarVariavel(TabelaSimbolos *tabela, const char *nomeVariavel) {
    // Validar se a variável já existe para não duplicar
    for (int i = 0; i < tabela->quantidade; i++) {
        if (strcmp(tabela->variaveis[i].nome, nomeVariavel) == 0) {
            return; // Variável já registrada, não faz nada
        }
    }

    // Registrar nova variável
    if (tabela->quantidade < 100) {
        strcpy(tabela->variaveis[tabela->quantidade].nome, nomeVariavel);
        tabela->quantidade++;
        printf(">> [MAPA DE MEMORIA]: Nova variavel alocada: '%s'\n", nomeVariavel);
    }
}

// Função para executar uma expressão
void executarExpressao(Expressao *expressao, TabelaSimbolos *tabelaMemoria, int linhaAtual) {

    // Devido não ser realizado cálculo, registra que a Linha X gerou uma expressão que terá um resultado no Assembly
    printf(">> [HISTORICO]: Preparando resultado da Linha %d para a keyword RES.\n", linhaAtual);

    // Percorre os tokens da expressão para identificar variáveis e registrar no mapa de memória
    for (int i = 0; i < expressao->tamanho; i++) {
        Token token = expressao->tokens[i];

        // Se o token for do tipo ALFA, é uma variável e deve ser registrada
        if (token.tipo == TOKEN_ALFA) { registrarVariavel(tabelaMemoria, token.valor); }

        // Se o token for a keyword RES, indica que o resultado dessa expressão deve ser armazenado para uso futuro
        else if (token.tipo == TOKEN_KEYWORD_RES) {
            printf(">> [SIMULACAO]: Comando RES detectado. O Assembly buscara no historico.\n");
        }

        // Se o token for um operador, indica que uma operação aritmética será realizada e deve ser empilhada para o Assembly
        else if (token.tipo == TOKEN_OPERADOR) {
            printf(">> [SIMULACAO]: Operacao '%s' empilhada para o Assembly.\n", token.valor);
        }
    }
}
