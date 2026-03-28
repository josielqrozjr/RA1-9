<h1 align="left">RA1-9 | Analisador Léxico e
Gerador de Assembly para ARMv7</h1>

<p align="left">
	<strong>PUCPR - Pontifícia Universidade Católica do Paraná</strong><br/>
	Bacharelado em Ciência da Computação
</p>

|  |  |
| --- | --- |
| Disciplina | Construção de Interpretadores (Turma 7º A) |
| Professor | Frank Alcantara |
| Aluno | Josiel Queiroz Júnior |
| GitHub | [josielqrozjr](https://github.com/josielqrozjr) |

## Sobre o projeto

Este projeto implementa um analisador léxico para expressões no formato esperado pela disciplina e gera código Assembly para ARMv7.

Fluxo geral:

1. Lê um arquivo de entrada com expressões linha a linha.
2. Tokeniza cada linha por meio da máquina de estados.
3. Valida a expressão (tratamento de exceções sintáticas/léxicas).
4. Executa regras de memória/histórico para símbolos e `RES`.
5. Gera o arquivo de saída `cpulatorAssembly.s`.

## Requisitos

- Linux (ou ambiente compatível com GCC)
- GCC com suporte a C11

## Como compilar

No diretório raiz do projeto, execute:

```bash
gcc -Wall -Wextra -std=c11 -o compilador \
	main.c lerArquivo.c parseExpressao.c maquinaEstados.c \
	excecoes.c executarExpressao.c gerarAssembly.c exibirResultados.c
```

Observação: podem aparecer warnings de compilação; o executável ainda é gerado.

## Como executar

Execute passando um arquivo de teste como argumento:

```bash
./compilador teste1.txt
```

Ao final da execução, o programa gera/atualiza o arquivo:

- `cpulatorAssembly.s` (Assembly ARMv7)

## Como testar

### Teste individual

```bash
./compilador teste1.txt
./compilador teste2.txt
./compilador teste3.txt
```

### Rodar todos os testes em sequência

```bash
for arq in teste1.txt teste2.txt teste3.txt; do
	echo "\n===== Executando $arq ====="
	./compilador "$arq"
done
```

### O que verificar nos testes

- Mensagens de leitura correta do arquivo.
- Tokenização válida nas linhas aceitas.
- Mensagens de erro sintático/léxico nas linhas inválidas.
- Resumo da memória mapeada ao final.
- Geração do arquivo `cpulatorAssembly.s`.

## Estrutura de arquivos

### Arquivos principais

- `main.c`: ponto de entrada; orquestra leitura, validação, execução e geração de Assembly.
- `assinatura.h`: structs, enums, constantes e assinaturas de funções.
- `README.md`: documentação do projeto.
- `LICENSE`: licença do repositório.

### Módulos de processamento

- `lerArquivo.c`: leitura do arquivo de entrada e separação das expressões.
- `parseExpressao.c`: tokenização da expressão.
- `maquinaEstados.c`: implementação da máquina de estados léxica.
- `excecoes.c`: validações e tratamento de erros de expressão.
- `executarExpressao.c`: processamento da expressão e controle de tabela de símbolos.
- `gerarAssembly.c`: geração do código Assembly ARMv7 e escrita do arquivo final.
- `exibirResultados.c`: relatório e saída de resultados no terminal.

### Entradas e saídas

- `teste1.txt`: conjunto de expressões para teste geral de operadores.
- `teste2.txt`: conjunto de expressões com foco em variáveis/memória e casos inválidos.
- `teste3.txt`: conjunto de expressões adicionais para cenários mistos.
- `cpulatorAssembly.s`: saída Assembly gerada pela última execução.
- `compilador`: executável gerado após compilação.