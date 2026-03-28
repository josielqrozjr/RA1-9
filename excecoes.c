/*
file: excecoes.c
Implementação das funções de tratamento de exceção.
Autor: Josiel Queiroz Júnior
GitHub: josielqrozjr
Grupo: RA1 9
*/

#include "assinatura.h"

// Função para validar a expressão e detectar erros comuns
bool validarExpressao(Expressao *expressao, int numeroLinha)
{
    int custoParenteses = 0; // Variável para controlar o custo dos parênteses
    int operandosPilha = 0;  // Variável para controlar o número de operandos na pilha
    Token ultimoOperando;    // Variável para armazenar o último operando para verificar divisão por zero

    // Exceção 1: Verificar se a expressão atingiu o limite máximo de tokens
    if (expressao->tamanho >= MAX_TOKEN_POR_EXPRESSAO && expressao->tokens[expressao->tamanho - 1].tipo != TOKEN_FIM)
    {
        printf("ERRO SINTATICO [Linha %d]: A expressao excedeu o limite maximo de %d tokens.\n", numeroLinha, MAX_TOKEN_POR_EXPRESSAO);
        return false;
    }

    for (int i = 0; i < expressao->tamanho; i++)
    {
        Token token = expressao->tokens[i];

        // Exceção 2: Verificar se o token está no formato correto (Caracteres estranhos, minúsculas, 3.14.5, 3,45)
        if (token.tipo == TOKEN_ERRO)
        {
            printf("ERRO LEXICO [Linha %d]: Token '%s' invalido.\n", numeroLinha, token.valor);
            return false;
        }

        // Exceção 3: Verificar se os parênteses estão balanceados e calcular o custo
        if (token.tipo == TOKEN_PAREN_ABERTURA)
        {
            custoParenteses++;
        }
        else if (token.tipo == TOKEN_PAREN_FECHADO)
        {
            custoParenteses--;
            if (custoParenteses < 0)
            {
                printf("ERRO SINTATICO [Linha %d]: Parenteses desbalanceados (fechamento ')' inesperado).\n", numeroLinha);
                return false;
            }
        }

        // Exceção 4: Verificar se os operadores estão válidos e validação semântica (divisão por zero, número de operandos)
        if (token.tipo == TOKEN_OPERADOR || token.tipo == TOKEN_KEYWORD_RES || token.tipo == TOKEN_ALFA)
        {
            operandosPilha++;
            ultimoOperando = token;
        }
        else if (token.tipo == TOKEN_OPERADOR)
        {

            // Cada operador binário precisa de pelo menos 2 operandos na pilha
            if (operandosPilha < 2)
            {
                printf("ERRO SEMANTICO [Linha %d]: Operacao invalida '%s'. Faltam numeros para calcular!\n", numeroLinha, token.valor);
                return false;
            }

            // Verificar divisão por zero
            if ((strcmp(token.valor, "/") == 0 || strcmp(token.valor, "//") == 0 || strcmp(token.valor, "%") == 0) && ultimoOperando.tipo == TOKEN_NUMERO && (strcmp(ultimoOperando.valor, "0") == 0 || strcmp(ultimoOperando.valor, "0.0") == 0))
            {

                printf("ERRO MATEMATICO [Linha %d]: Divisao por zero detectada antes da operacao '%s'.\n", numeroLinha, token.valor);
                return false;
            }

            // Consumir 2 números e devolve 1 resultado para a pilha
            operandosPilha--;

            // Atualizar o último operando para o resultado da operação, para verificar futuras divisões por zero
            ultimoOperando.tipo = TOKEN_NUMERO;
            strcpy(ultimoOperando.valor, "RESULTADO_VIRTUAL"); // Placeholder para o resultado da operação
        }
    }

    // Exceção 5: Verificar se os parênteses estão balanceados no final da expressão
    if (custoParenteses != 0)
    {
        printf("ERRO SINTATICO [Linha %d]: Parenteses desbalanceados (falta fechar %d parenteses).\n", numeroLinha, custoParenteses);
        return false;
    }

    // Verifica se a expressão RPN resultou em um único valor final na pilha
    // Caso a pilha tenha mais de 1 item no final (ex: "2 2 + 3 4"), então falta operador para combinar os operandos restantes
    if (operandosPilha > 1)
    {
        printf("ERRO SINTATICO [Linha %d]: Formato RPN invalido. Sobraram operandos sem operadores.\n", numeroLinha);
        return false;
    }

    return true;
}
