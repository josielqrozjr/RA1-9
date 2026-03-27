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
    
}