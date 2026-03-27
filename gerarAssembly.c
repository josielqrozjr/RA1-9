/*
file: gerarAssembly.c
Implementação das funções de geração de código Assembly ARMv7 (IEEE 754).
Autor: Josiel Queiroz Júnior
GitHub: josielqrozjr
Grupo: RA1 9
*/

#include "assinatura.h"

static int rotuloMemoria = 0; // Variável global para controle de rótulos

void gerarAssembly(Expressao *expressao, char *codigoAssembly)
{
    char instrucao[512];

    // Gerar código Assembly para cada token na expressão
    for (int i = 0; i < expressao->tamanho; i++)
    {
        Token token = expressao->tokens[i];

        switch (token.tipo)
        {
        case TOKEN_NUMERO:
            // Gerar código para carregar um número em um registrador
            snprintf(instrucao, sizeof(instrucao),
                    "@ Carregando numero %s\n"
                    "LDR r0, =const_%d    @ Endereco do numero na RAM\n"
                    "VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0\n"
                    "VPUSH {D0}           @ Empilhar na pilha RPN\n",
                    token.valor, rotuloMemoria);
            strcat(codigoAssembly, instrucao);
            rotuloMemoria++;
            break;

        case TOKEN_ALFA:
            // Gerar código para carregar uma variável (letra) em um registrador
            snprintf(instrucao, sizeof(instrucao),
                    "@ Salvando na memoria: %s\n"
                    "VPOP {D0}            @ Desempilhar o resultado\n"
                    "LDR r0, =var_%s      @ Capturar endereco da variavel\n"
                    "VSTR.F64 D0, [r0]    @ Salvar na RAM\n", 
                    token.valor, token.valor);
            strcat(codigoAssembly, instrucao);
            break;

        case TOKEN_OPERADOR:
            // Gerar código para operadores aritméticos
            // Lógica RPN: Desempilha B (direita), desempilha A (esquerda), calcula, empilha resultado
            strcat(codigoAssembly, "@ Operacao Matematica\n");
            strcat(codigoAssembly, "VPOP {D1}            @ B (Operando Direita)\n");
            strcat(codigoAssembly, "VPOP {D0}            @ A (Operando Esquerda)\n");

            if (strcmp(token.valor, "+") == 0) {
                strcat(codigoAssembly, "VADD.F64 D2, D0, D1  @ D2 = A + B\n");
            } else if (strcmp(token.valor, "-") == 0) {
                strcat(codigoAssembly, "VSUB.F64 D2, D0, D1  @ D2 = A - B\n");
            } else if (strcmp(token.valor, "*") == 0) {
                strcat(codigoAssembly, "VMUL.F64 D2, D0, D1  @ D2 = A * B\n");
            } else if (strcmp(token.valor, "/") == 0) {
                strcat(codigoAssembly, "VDIV.F64 D2, D0, D1  @ D2 = A / B\n");
            }
            // TO DO: Implementar em partes para validar Operações inteiras (//, %, ^) com conversão VCVT.F64.S32
            
            strcat(codigoAssembly, "VPUSH {D2}           @ Empilhar resultado\n");
        }
    }
}
