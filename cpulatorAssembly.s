.data
const_0: .double 3.5
const_1: .double 2.0
const_2: .double 10.0
const_3: .double 4.5
const_4: .double 2.0
const_5: .double 3.0
const_6: .double 8.0
const_7: .double 2.0
const_8: .double 10.0
const_9: .double 3.0
const_10: .double 10.0
const_11: .double 3.0
const_12: .double 2.0
const_13: .double 3
const_14: .double 42.0
const_15: .double 1

@ Variaveis de Memoria (8 bytes = 64 bits)
var_X: .space 8

@ Historico de resultados (RES) - Suporta ate 100 linhas
historico_res: .space 800

.text
.global _start
_start:

    @ Carregando numero 3.5
    LDR r0, =const_0    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 2.0
    LDR r0, =const_1    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: +
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VADD.F64 D2, D0, D1  @ D2 = A + B
    VPUSH {D2}           @ Empilhar resultado

    @ -- Fim da Linha 1: Salvando no historico --
    VPOP {D0}            @ Copia o resultado final da linha
    LDR r0, =historico_res
    LDR r1, =0          @ Indice da linha (0-based)
    MOV r2, #8           @ 8 bytes por double
    MUL r1, r1, r2       @ Offset
    ADD r0, r0, r1       @ Endereco do historico
    VSTR.F64 D0, [r0]    @ Salva no array historico_res
    VPUSH {D0}           @ Devolve para a pilha RPN

    @ Carregando numero 10.0
    LDR r0, =const_2    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 4.5
    LDR r0, =const_3    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: -
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VSUB.F64 D2, D0, D1  @ D2 = A - B
    VPUSH {D2}           @ Empilhar resultado

    @ -- Fim da Linha 2: Salvando no historico --
    VPOP {D0}            @ Copia o resultado final da linha
    LDR r0, =historico_res
    LDR r1, =1          @ Indice da linha (0-based)
    MOV r2, #8           @ 8 bytes por double
    MUL r1, r1, r2       @ Offset
    ADD r0, r0, r1       @ Endereco do historico
    VSTR.F64 D0, [r0]    @ Salva no array historico_res
    VPUSH {D0}           @ Devolve para a pilha RPN

    @ Carregando numero 2.0
    LDR r0, =const_4    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 3.0
    LDR r0, =const_5    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: *
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VMUL.F64 D2, D0, D1  @ D2 = A * B
    VPUSH {D2}           @ Empilhar resultado

    @ -- Fim da Linha 3: Salvando no historico --
    VPOP {D0}            @ Copia o resultado final da linha
    LDR r0, =historico_res
    LDR r1, =2          @ Indice da linha (0-based)
    MOV r2, #8           @ 8 bytes por double
    MUL r1, r1, r2       @ Offset
    ADD r0, r0, r1       @ Endereco do historico
    VSTR.F64 D0, [r0]    @ Salva no array historico_res
    VPUSH {D0}           @ Devolve para a pilha RPN

    @ Carregando numero 8.0
    LDR r0, =const_6    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 2.0
    LDR r0, =const_7    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: /
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VDIV.F64 D2, D0, D1  @ D2 = A / B
    VPUSH {D2}           @ Empilhar resultado

    @ -- Fim da Linha 4: Salvando no historico --
    VPOP {D0}            @ Copia o resultado final da linha
    LDR r0, =historico_res
    LDR r1, =3          @ Indice da linha (0-based)
    MOV r2, #8           @ 8 bytes por double
    MUL r1, r1, r2       @ Offset
    ADD r0, r0, r1       @ Endereco do historico
    VSTR.F64 D0, [r0]    @ Salva no array historico_res
    VPUSH {D0}           @ Devolve para a pilha RPN

    @ Carregando numero 10.0
    LDR r0, =const_8    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 3.0
    LDR r0, =const_9    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: //
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VDIV.F64 D2, D0, D1  @ D2 = A / B (Divisao real, ex: 3.33)
    VCVT.S32.F64 S4, D2  @ Converte para Int32 (Trunca os decimais, vira 3)
    VCVT.F64.S32 D2, S4  @ Converte de volta para Float64 (3.0)
    VPUSH {D2}           @ Empilhar resultado

    @ -- Fim da Linha 5: Salvando no historico --
    VPOP {D0}            @ Copia o resultado final da linha
    LDR r0, =historico_res
    LDR r1, =4          @ Indice da linha (0-based)
    MOV r2, #8           @ 8 bytes por double
    MUL r1, r1, r2       @ Offset
    ADD r0, r0, r1       @ Endereco do historico
    VSTR.F64 D0, [r0]    @ Salva no array historico_res
    VPUSH {D0}           @ Devolve para a pilha RPN

    @ Carregando numero 10.0
    LDR r0, =const_10    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 3.0
    LDR r0, =const_11    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: %
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VDIV.F64 D2, D0, D1  @ D2 = A / B
    VCVT.S32.F64 S4, D2  @ Trunca para inteiro (Quociente)
    VCVT.F64.S32 D2, S4  @ D2 = Quociente em Float64
    VMUL.F64 D2, D2, D1  @ D2 = Quociente * Divisor
    VSUB.F64 D2, D0, D2  @ D2 = A - (Quociente * Divisor) = Resto!
    VPUSH {D2}           @ Empilhar resultado

    @ -- Fim da Linha 6: Salvando no historico --
    VPOP {D0}            @ Copia o resultado final da linha
    LDR r0, =historico_res
    LDR r1, =5          @ Indice da linha (0-based)
    MOV r2, #8           @ 8 bytes por double
    MUL r1, r1, r2       @ Offset
    ADD r0, r0, r1       @ Endereco do historico
    VSTR.F64 D0, [r0]    @ Salva no array historico_res
    VPUSH {D0}           @ Devolve para a pilha RPN

    @ Carregando numero 2.0
    LDR r0, =const_12    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 3
    LDR r0, =const_13    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: ^
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VCVT.S32.F64 S2, D1  @ Converte Expoente B para Int32
    VMOV r1, S2          @ r1 = Contador de loop
    MOV r2, #1           @ Prepara o numero 1 inteiro
    VMOV S4, r2          
    VCVT.F64.S32 D2, S4  @ Inicia Resultado D2 = 1.0
loop_pot_0:
    CMP r1, #0           @ Se contador <= 0, acaba
    BLE fim_pot_0
    VMUL.F64 D2, D2, D0  @ Resultado = Resultado * Base
    SUB r1, r1, #1       @ Contador--
    B loop_pot_0
fim_pot_0:
    VPUSH {D2}           @ Empilhar resultado

    @ -- Fim da Linha 7: Salvando no historico --
    VPOP {D0}            @ Copia o resultado final da linha
    LDR r0, =historico_res
    LDR r1, =6          @ Indice da linha (0-based)
    MOV r2, #8           @ 8 bytes por double
    MUL r1, r1, r2       @ Offset
    ADD r0, r0, r1       @ Endereco do historico
    VSTR.F64 D0, [r0]    @ Salva no array historico_res
    VPUSH {D0}           @ Devolve para a pilha RPN

    @ Carregando numero 42.0
    LDR r0, =const_14    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Salvando na memoria: X
    VPOP {D0}            @ Desempilhar o resultado
    LDR r0, =var_X      @ Capturar endereco da variavel
    VSTR.F64 D0, [r0]    @ Salvar na RAM
    VPUSH {D0}           @ Re-empilha para manter integridade da linha

    @ -- Fim da Linha 8: Salvando no historico --
    VPOP {D0}            @ Copia o resultado final da linha
    LDR r0, =historico_res
    LDR r1, =7          @ Indice da linha (0-based)
    MOV r2, #8           @ 8 bytes por double
    MUL r1, r1, r2       @ Offset
    ADD r0, r0, r1       @ Endereco do historico
    VSTR.F64 D0, [r0]    @ Salva no array historico_res
    VPUSH {D0}           @ Devolve para a pilha RPN

    @ Carregando numero 1
    LDR r0, =const_15    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Comando RES detectado
    VPOP {D0}            @ Retira N (qtd de linhas anteriores) em Float64
    VCVT.S32.F64 S0, D0  @ Converte N float para Inteiro
    VMOV r1, S0          @ r1 = N
    LDR r2, =9          @ r2 = Linha atual (1-based)
    SUB r3, r2, r1       @ r3 = Linha alvo (Linha atual - N)
    SUB r3, r3, #1       @ r3 = Indice no array historico_res (0-based)
    LDR r0, =historico_res
    MOV r4, #8           @ 8 bytes por double (IEEE 754)
    MUL r3, r3, r4       @ Calcula offset (Indice * 8)
    ADD r0, r0, r3       @ Endereco = historico_res + offset
    VLDR.F64 D2, [r0]    @ Carrega o valor do historico
    VPUSH {D2}           @ Empilha o resultado

    @ -- Fim da Linha 9: Salvando no historico --
    VPOP {D0}            @ Copia o resultado final da linha
    LDR r0, =historico_res
    LDR r1, =8          @ Indice da linha (0-based)
    MOV r2, #8           @ 8 bytes por double
    MUL r1, r1, r2       @ Offset
    ADD r0, r0, r1       @ Endereco do historico
    VSTR.F64 D0, [r0]    @ Salva no array historico_res
    VPUSH {D0}           @ Devolve para a pilha RPN

fim:
    B fim

