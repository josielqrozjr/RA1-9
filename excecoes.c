/*
file: excecoes.c
Implementação das validações léxicas e sintáticas para tratamento de erros.
Autor: Josiel Queiroz Júnior
GitHub: josielqrozjr
Grupo: RA1 9
*/

#include "assinatura.h"

// Retorna true (1) se a expressão for válida e false (0) se contiver erros
bool validarExpressao(Expressao *exp, int numeroLinha) {
    int saldoParenteses = 0;
    int operandosNaPilha = 0; 
    Token ultimoOperando; // Guarda o último operando para verificar divisão por zero

    // 1. Excesso de tokens
    if (exp->tamanho >= MAX_TOKEN_POR_EXPRESSAO && exp->tokens[exp->tamanho - 1].tipo != TOKEN_FIM) {
        printf("ERRO SINTATICO [Linha %d]: A expressao excedeu o limite maximo de tokens.\n", numeroLinha);
        return false;
    }

    for (int i = 0; i < exp->tamanho; i++) {
        Token t = exp->tokens[i];

        // 2. Erros Léxicos
        if (t.tipo == TOKEN_ERRO) {
            printf("ERRO LEXICO [Linha %d]: Token '%s' invalido.\n", numeroLinha, t.valor);
            return false;
        }

        // 3. Parênteses
        if (t.tipo == TOKEN_PAREN_ABERTURA) {
            saldoParenteses++;
        } 
        else if (t.tipo == TOKEN_PAREN_FECHADO) {
            saldoParenteses--;
            if (saldoParenteses < 0) {
                printf("ERRO SINTATICO [Linha %d]: Parenteses desbalanceados (fechamento ')' inesperado).\n", numeroLinha);
                return false;
            }
        }

        // 4. Simulador de Pilha e Validação Semântica
        if (t.tipo == TOKEN_NUMERO || t.tipo == TOKEN_ALFA) { // CORREÇÃO: Trata ALFA como operando válido
            operandosNaPilha++;
            ultimoOperando = t; 
        } 
        else if (t.tipo == TOKEN_KEYWORD_RES) {
            if (operandosNaPilha < 1) {
                printf("ERRO SEMANTICO [Linha %d]: O comando RES precisa de um número 'N' antes dele.\n", numeroLinha);
                return false;
            }
            // O RES consome o N e coloca 1 resultado na pilha
            ultimoOperando.tipo = TOKEN_NUMERO;
            strcpy(ultimoOperando.valor, "RESULTADO_RES");
        }
        else if (t.tipo == TOKEN_OPERADOR) {
            
            // Verifica Falta de Operandos
            if (operandosNaPilha < 2) {
                printf("ERRO SEMANTICO [Linha %d]: Operacao '%s' invalida. Faltam operandos!\n", numeroLinha, t.valor);
                return false;
            }
            
            // Verifica Divisão por Zero
            if ((strcmp(t.valor, "/") == 0 || strcmp(t.valor, "//") == 0 || strcmp(t.valor, "%") == 0) && 
                ultimoOperando.tipo == TOKEN_NUMERO && 
                (strcmp(ultimoOperando.valor, "0") == 0 || strcmp(ultimoOperando.valor, "0.0") == 0)) {
                
                printf("ERRO MATEMATICO [Linha %d]: Divisao por zero detectada antes da operacao '%s'.\n", numeroLinha, t.valor);
                return false;
            }

            // Consome 2 operandos e devolve 1 resultado para a pilha
            operandosNaPilha--; 
            
            ultimoOperando.tipo = TOKEN_NUMERO; 
            strcpy(ultimoOperando.valor, "RESULTADO_VIRTUAL");
        }
    }

    if (saldoParenteses != 0) {
        printf("ERRO SINTATICO [Linha %d]: Parenteses desbalanceados (falta fechar %d parenteses).\n", numeroLinha, saldoParenteses);
        return false;
    }
    
    // Se o último token útil foi uma Variável, não é exigido operador
    Token ultimoTokenUtil;
    for (int k = exp->tamanho - 1; k >= 0; k--) {
        if (exp->tokens[k].tipo != TOKEN_FIM && exp->tokens[k].tipo != TOKEN_PAREN_FECHADO) {
            ultimoTokenUtil = exp->tokens[k];
            break;
        }
    }

    if (ultimoTokenUtil.tipo == TOKEN_ALFA) {
        operandosNaPilha--; // A variável recebe o valor que estava antes dela
    }

    if (operandosNaPilha > 1) {
        printf("ERRO SINTATICO [Linha %d]: Formato RPN invalido. Sobraram operandos sem operadores.\n", numeroLinha);
        return false;
    }

    return true; 
}
