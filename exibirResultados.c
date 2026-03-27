/*
file: exibirResultados.c
Implementação das funções de exibição de resultados com relatório
da compilação, incluindo erros, variáveis mapeadas e exportar
o arquivo Assembly.
*/

#include "assinatura.h"

static const char *nomeArquivoAssembly = "cpulatorAssembly.s";

void exibirResultados(double *resultados, int quantResultados, const char *codigoAssembly)
{

    printf("\n*** FASE DE COMPILACAO CONCLUIDA ***\n");
    printf("Status: SUCESSO.\n");

    FILE *arquivoAssembly = fopen(nomeArquivoAssembly, "w");
    if (arquivoAssembly != NULL)
    {

        // Escrever o header obrigatório do Assembly ARMv7
        fprintf(arquivoAssembly, ".global _start\n");
        fprintf(arquivoAssembly, ".text\n");
        fprintf(arquivoAssembly, "_start:\n");

        // Escrever o código que nós geramos
        fprintf(arquivoAssembly, "%s", codigoAssembly);

        // Loop infinito para segurar a placa do CPULATOR ligada no final
        fprintf(arquivoAssembly, "fim:\n    B fim\n\n");

        // TO DO: A seção .data com as variáveis será declarada aqui depois.

        fclose(arquivoAssembly);
        printf("-> Arquivo '%s' gerado com sucesso!\n", nomeArquivoAssembly);
        printf("-> Para ver os resultados das operacoes, abra este arquivo no CPULATOR (ARMv7).\n");
    }
    else
    {
        printf("ERRO: Nao foi possivel criar o arquivo de Assembly.\n");
    }
    printf("************************************\n");
}
