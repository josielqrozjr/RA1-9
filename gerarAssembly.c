/*
file: gerarAssembly.c
Implementação das funções de geração de código Assembly ARMv7 (IEEE 754).
Autor: Josiel Queiroz Júnior
GitHub: josielqrozjr
Grupo: RA1 9
*/

#include "assinatura.h"

static int rotuloMemoria = 0;       // Variável global para controle de rótulos
static int rotuloLoop = 0;          // Variável global para controle de loop, como pontenciação
static int linhaAtualCompilada = 1; // Variável global para controle de linha atual compilada, usada no comando RES

void gerarAssembly(Expressao *expressao, char *codigoAssembly, char *dadosAssembly)
{
    char instrucao[2048] = {0};
    char dado[1024] = {0};

    // Gerar código Assembly para cada token na expressão
    for (int i = 0; i < expressao->tamanho; i++)
    {
        Token token = expressao->tokens[i];

        switch (token.tipo)
        {
        case TOKEN_NUMERO:

            // Gerar um rótulo único para o número e armazenar na memória de dados em 64 bits
            snprintf(dado, sizeof(dado), "const_%d: .double %s\n", rotuloMemoria, token.valor);
            strcat(dadosAssembly, dado);

            // Gerar código para carregar um número em um registrador
            snprintf(instrucao, sizeof(instrucao),
                     "    @ Carregando numero %s\n"
                     "    LDR r0, =const_%d    @ Endereco do numero na RAM\n"
                     "    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0\n"
                     "    VPUSH {D0}           @ Empilhar na pilha RPN\n\n",
                     token.valor, rotuloMemoria);
            strcat(codigoAssembly, instrucao);
            rotuloMemoria++;
            break;

        case TOKEN_ALFA:
            // Caso a variável for o último token antes do fechamento do parêntese e precedida por um valor, é escrita
            // Caso contrário (ex: (X 2 +)), é leitura
            if (i + 1 < expressao->tamanho && expressao->tokens[i + 1].tipo != TOKEN_PAREN_FECHADO)
            {
                // Leitura da memória (Caso de variável seguida por operador ou número)
                snprintf(instrucao, sizeof(instrucao),
                         "    @ Lendo variavel: %s\n"
                         "    LDR r0, =var_%s      @ Capturar endereco da variavel\n"
                         "    VLDR.F64 D0, [r0]    @ Carrega valor da RAM\n"
                         "    VPUSH {D0}           @ Empilha na RPN\n\n",
                         token.valor, token.valor);
            }
            else if (i > 0 && expressao->tokens[i - 1].tipo == TOKEN_PAREN_ABERTURA)
            {
                // Leitura da memória (Caso de variável isolada)
                snprintf(instrucao, sizeof(instrucao),
                         "    @ Lendo variavel: %s\n"
                         "    LDR r0, =var_%s      @ Capturar endereco da variavel\n"
                         "    VLDR.F64 D0, [r0]    @ Carrega valor da RAM\n"
                         "    VPUSH {D0}           @ Empilha na RPN\n\n",
                         token.valor, token.valor);
            }
            else
            {
                // Escrita na memória (Caso de variável seguida por fechamento de parêntese, ex: (X 2 +) X)
                snprintf(instrucao, sizeof(instrucao),
                         "    @ Salvando na memoria: %s\n"
                         "    VPOP {D0}            @ Desempilhar o resultado\n"
                         "    LDR r0, =var_%s      @ Capturar endereco da variavel\n"
                         "    VSTR.F64 D0, [r0]    @ Salvar na RAM\n"
                         "    VPUSH {D0}           @ Re-empilha para manter integridade da linha\n\n",
                         token.valor, token.valor);
            }
            strcat(codigoAssembly, instrucao);
            break;

        case TOKEN_KEYWORD_RES:
            // O comando (N RES) busca o histórico. Retira N da pilha e busca no array
            snprintf(instrucao, sizeof(instrucao),
                     "    @ Comando RES detectado\n"
                     "    VPOP {D0}            @ Retira N (qtd de linhas anteriores) em Float64\n"
                     "    VCVT.S32.F64 S0, D0  @ Converte N float para Inteiro\n"
                     "    VMOV r1, S0          @ r1 = N\n"
                     "    LDR r2, =%d          @ r2 = Linha atual (1-based)\n"
                     "    SUB r3, r2, r1       @ r3 = Linha alvo (Linha atual - N)\n"
                     "    SUB r3, r3, #1       @ r3 = Indice no array historico_res (0-based)\n"
                     "    LDR r0, =historico_res\n"
                     "    MOV r4, #8           @ 8 bytes por double (IEEE 754)\n"
                     "    MUL r3, r3, r4       @ Calcula offset (Indice * 8)\n"
                     "    ADD r0, r0, r3       @ Endereco = historico_res + offset\n"
                     "    VLDR.F64 D2, [r0]    @ Carrega o valor do historico\n"
                     "    VPUSH {D2}           @ Empilha o resultado\n\n",
                     linhaAtualCompilada);
            strcat(codigoAssembly, instrucao);
            break;

        case TOKEN_OPERADOR:
            // Gerar código para operadores aritméticos
            // Lógica RPN: Desempilha B (direita), desempilha A (esquerda), calcula, empilha resultado
            strcat(codigoAssembly, "    @ Operacao Matematica: "); // NOVO: Protege como comentário
            strcat(codigoAssembly, token.valor);
            strcat(codigoAssembly, "\n");
            strcat(codigoAssembly, "    VPOP {D1}            @ B (Operando Direita)\n");
            strcat(codigoAssembly, "    VPOP {D0}            @ A (Operando Esquerda)\n");

            // Operaçòes com números reais
            if (strcmp(token.valor, "+") == 0)
            {
                strcat(codigoAssembly, "    VADD.F64 D2, D0, D1  @ D2 = A + B\n");
            }
            else if (strcmp(token.valor, "-") == 0)
            {
                strcat(codigoAssembly, "    VSUB.F64 D2, D0, D1  @ D2 = A - B\n");
            }
            else if (strcmp(token.valor, "*") == 0)
            {
                strcat(codigoAssembly, "    VMUL.F64 D2, D0, D1  @ D2 = A * B\n");
            }
            else if (strcmp(token.valor, "/") == 0)
            {
                strcat(codigoAssembly, "    VDIV.F64 D2, D0, D1  @ D2 = A / B\n");
            }

            // Operações com números inteiros
            else if (strcmp(token.valor, "//") == 0)
            {
                snprintf(instrucao, sizeof(instrucao),
                         "    VDIV.F64 D2, D0, D1  @ D2 = A / B (Divisao real, ex: 3.33)\n"
                         "    VCVT.S32.F64 S4, D2  @ Converte para Int32 (Trunca os decimais, vira 3)\n"
                         "    VCVT.F64.S32 D2, S4  @ Converte de volta para Float64 (3.0)\n");
                strcat(codigoAssembly, instrucao);
            }
            else if (strcmp(token.valor, "%") == 0)
            {
                // Matemática do resto: Resto = A - (int(A / B) * B)
                snprintf(instrucao, sizeof(instrucao),
                         "    VDIV.F64 D2, D0, D1  @ D2 = A / B\n"
                         "    VCVT.S32.F64 S4, D2  @ Trunca para inteiro (Quociente)\n"
                         "    VCVT.F64.S32 D2, S4  @ D2 = Quociente em Float64\n"
                         "    VMUL.F64 D2, D2, D1  @ D2 = Quociente * Divisor\n"
                         "    VSUB.F64 D2, D0, D2  @ D2 = A - (Quociente * Divisor) = Resto!\n");
                strcat(codigoAssembly, instrucao);
            }
            else if (strcmp(token.valor, "^") == 0)
            {
                // Para potenciação em Assembly multiplica-se A por ele mesmo B vezes, por isso exige um loop
                snprintf(instrucao, sizeof(instrucao),
                         "    VCVT.S32.F64 S2, D1  @ Converte Expoente B para Int32\n"
                         "    VMOV r1, S2          @ r1 = Contador de loop\n"
                         "    MOV r2, #1           @ Prepara o numero 1 inteiro\n"
                         "    VMOV S4, r2          \n"
                         "    VCVT.F64.S32 D2, S4  @ Inicia Resultado D2 = 1.0\n"
                         "loop_pot_%d:\n"
                         "    CMP r1, #0           @ Se contador <= 0, acaba\n"
                         "    BLE fim_pot_%d\n"
                         "    VMUL.F64 D2, D2, D0  @ Resultado = Resultado * Base\n"
                         "    SUB r1, r1, #1       @ Contador--\n"
                         "    B loop_pot_%d\n"
                         "fim_pot_%d:\n",
                         rotuloLoop, rotuloLoop, rotuloLoop, rotuloLoop);
                strcat(codigoAssembly, instrucao);
                rotuloLoop++;
            }

            strcat(codigoAssembly, "    VPUSH {D2}           @ Empilhar resultado\n\n");
            break;
        }
    }

    // Ao final da linha, salvar o resultado no histórico (último resultado fica no topo da pilha RPN)
    snprintf(instrucao, sizeof(instrucao),
             "    @ -- Fim da Linha %d: Salvando no historico --\n"
             "    VPOP {D0}            @ Copia o resultado final da linha\n"
             "    LDR r0, =historico_res\n"
             "    LDR r1, =%d          @ Indice da linha (0-based)\n"
             "    MOV r2, #8           @ 8 bytes por double\n"
             "    MUL r1, r1, r2       @ Offset\n"
             "    ADD r0, r0, r1       @ Endereco do historico\n"
             "    VSTR.F64 D0, [r0]    @ Salva no array historico_res\n"
             "    VPUSH {D0}           @ Devolve para a pilha RPN\n\n",
             linhaAtualCompilada, linhaAtualCompilada - 1);
    strcat(codigoAssembly, instrucao);

    // Preparar para a próxima linha de teste
    linhaAtualCompilada++;
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

    // Array para guardar o histórico de resultados (RES)
    fprintf(arquivo, "\n@ Historico de resultados (RES) - Suporta ate 100 linhas\n");
    fprintf(arquivo, "historico_res: .space 800\n");

    // Escrever a seção de código
    fprintf(arquivo, "\n.text\n");
    fprintf(arquivo, ".global _start\n");
    fprintf(arquivo, "_start:\n\n");

    fprintf(arquivo, "%s", codigoAssembly);
    fprintf(arquivo, "fim:\n    B fim\n\n");

    fclose(arquivo);
    return 1;
}
