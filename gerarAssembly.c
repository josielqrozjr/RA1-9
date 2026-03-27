/*
file: gerarAssembly.c
Implementação das funções de geração de código Assembly ARMv7 (IEEE 754).
Autor: Josiel Queiroz Júnior
GitHub: josielqrozjr
Grupo: RA1 9
*/

#include "assinatura.h"

static int rotuloMemoria = 0; // Variável global para controle de rótulos

void gerarAssembly(Expressao *expressao, char *codigoAssembly, char *dadosAssembly)
{
    char instrucao[1024];
    char dado[1024];

    // Gerar código Assembly para cada token na expressão
    for (int i = 0; i < expressao->tamanho; i++)
    {
        Token token = expressao->tokens[i];

        switch (token.tipo)
        {
        case TOKEN_NUMERO:

            // Gerar um rótulo único para o número e armazenar na memória de dados
            snprintf(dado, sizeof(dado), "const_%d: .double %s\n", rotuloMemoria, token.valor);
            strcat(dadosAssembly, dado);

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

            if (strcmp(token.valor, "+") == 0)
            {
                strcat(codigoAssembly, "VADD.F64 D2, D0, D1  @ D2 = A + B\n");
            }
            else if (strcmp(token.valor, "-") == 0)
            {
                strcat(codigoAssembly, "VSUB.F64 D2, D0, D1  @ D2 = A - B\n");
            }
            else if (strcmp(token.valor, "*") == 0)
            {
                strcat(codigoAssembly, "VMUL.F64 D2, D0, D1  @ D2 = A * B\n");
            }
            else if (strcmp(token.valor, "/") == 0)
            {
                strcat(codigoAssembly, "VDIV.F64 D2, D0, D1  @ D2 = A / B\n");
            }
            // TO DO: Implementar em partes para validar Operações inteiras (//, %, ^) com conversão VCVT.F64.S32

            strcat(codigoAssembly, "VPUSH {D2}           @ Empilhar resultado\n");
        }
    }
}

// Função auxiliar para salvar o código Assembly em um arquivo
int salvarAssembly(const char *nomeArquivo, const char *codigoAssembly, const char *dadosAssembly, TabelaSimbolos *tabelaMemoria)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        printf("ERRO: Nao foi possivel criar o arquivo de Assembly '%s'.\n", nomeArquivo);
        return 0;
    }

    // Escrever a seção de dados
    fprintf(arquivo, ".data\n");
    fprintf(arquivo, "%s", dadosAssembly);

    // Imprime o espaço na memória para as variáveis em 64 bits (8 bytes)
    fprintf(arquivo, "\n@ Variaveis de Memoria (8 bytes = 64 bits)\n");
    for (int i = 0; i < tabelaMemoria->quantidade; i++)
    {
        fprintf(arquivo, "var_%s: .space 8\n", tabelaMemoria->variaveis[i].nome);
    }

    // Escrever a seção de código
    fprintf(arquivo, "\n.text\n");
    fprintf(arquivo, ".global _start\n");
    fprintf(arquivo, "_start:\n\n");
    
    fprintf(arquivo, "%s", codigoAssembly);
    fprintf(arquivo, "fim:\n    B fim\n\n");
    
    fclose(arquivo);
    return 1;
}
