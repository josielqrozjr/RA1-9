/*
file: main.c
Função principal da aplicação.
Autor: Josiel Queiroz Júnior
GitHub: josielqrozjr
Grupo: RA1 9
*/

#include "assinatura.h"

// Função auxiliar para debugar e ver se os tokens foram gerados corretamente
void imprimirTokens(Expressao exp)
{
    for (int i = 0; i < exp.tamanho; i++)
    {
        Token t = exp.tokens[i];
        printf("[Tipo: %d | Valor: '%s'] ", t.tipo, t.valor);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    // Validação de Argumentos de Linha de Comando
    if (argc != 2)
    {
        printf("USO INCORRETO!\n");
        printf("Como usar: %s <arquivo_de_teste.txt>\n", argv[0]);
        return 1;
    }

    char *nomeArquivo = argv[1];

    // Matriz para guardar até 100 expressões de até 256 caracteres
    char linhasTexto[100][MAX_TOKEN_POR_EXPRESSAO];
    int quantidadeLinhas = 0;

    // Leitura do Arquivo
    if (!lerArquivo(nomeArquivo, linhasTexto, &quantidadeLinhas))
    {
        return 1; // Encerrar se der erro na leitura
    }

    printf("Arquivo '%s' lido com sucesso! (%d linhas encontradas)\n", nomeArquivo, quantidadeLinhas);
    printf("--------------------------------------------------\n");

    // Criar tabela de símbolos para gerenciar variáveis e seus valores
    TabelaSimbolos tabelaMemoria;
    tabelaMemoria.quantidade = 0;       // Inicializa a quantidade de variáveis registradas
    char bufferAssembly[10000] = "";    // Buffer para acumular o código Assembly gerado

    // Processamento Lexical e Validação de Exceções
    for (int i = 0; i < quantidadeLinhas; i++)
    {
        printf("\nProcessando Linha %d: %s\n", i + 1, linhasTexto[i]);

        // Analisar cada expressão e gerar os tokens
        Expressao expressaoTokenizada = parseExpressao(linhasTexto[i]);

        // Usar exceções para validar a expressão e detectar erros comuns
        if (!validarExpressao(&expressaoTokenizada, i + 1))
        {
            printf(">>> Linha %d ignorada devido a erros.\n", i + 1);
            continue; // Pula para a próxima linha do arquivo
        }

        // Caso tenha passado na validação, imprime os tokens com sucesso
        printf("Tokens Validos:  ");
        imprimirTokens(expressaoTokenizada);

        // Executar a expressão e gerenciar o mapa de memória para variáveis, preparando para a geração de Assembly
        executarExpressao(&expressaoTokenizada, &tabelaMemoria, i + 1);

        // Gerar o código Assembly correspondente à expressão processada
        gerarAssembly(&expressaoTokenizada, bufferAssembly);
    }

    // Mostra o resumo da memória mapeada no final
    printf("\n=== RESUMO DA MEMORIA MAPEADA ===\n");
    printf("Total de Variaveis (MEM): %d\n", tabelaMemoria.quantidade);
    for (int v = 0; v < tabelaMemoria.quantidade; v++) {
        printf("- %s\n", tabelaMemoria.variaveis[v].nome);
    }
    printf("************************************\n");

    // Exibir os resultados finais, incluindo o código Assembly gerado e o relatório de compilação
    exibirResultados(NULL, 0, bufferAssembly);

    return 0;
}
