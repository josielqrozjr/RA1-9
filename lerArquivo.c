/*
file: lerArquivo.c
Implementação das funções de leitura de arquivos.
*/

#include "assinatura.h"

// Função para ler expressões de um arquivo e armazená-las em um array
int lerArquivo(const char* nomeArquivo, char expressoes[][MAX_TOKEN_POR_EXPRESSAO], int* quantExpressoes) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("ERRO: Ao abrir o arquivo: %s\n", nomeArquivo);
        return 0; // Retornar 0 para indicar falha na leitura
    }

    *quantExpressoes = 0;
    char buffer[MAX_TOKEN_POR_EXPRESSAO];

    // Ler o arquivo linha por linha
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        // Remove a quebra de linha (\n ou \r) do final da string lida, se houver
        buffer[strcspn(buffer, "\r\n")] = 0;

        // Ignorar linhas vazias
        if (strlen(buffer) > 0) {
            strcpy(expressoes[*quantExpressoes], buffer);
            (*quantExpressoes)++;
        }
    }

    fclose(arquivo);
    return 1; // Retornar 1 para indicar sucesso na leitura
}
