.data
const_0: .double 2
const_1: .double 2
const_2: .double 5
const_3: .double 3
const_4: .double 4
const_5: .double 3
const_6: .double 8
const_7: .double 2

@ Variaveis de Memoria (8 bytes = 64 bits)

.text
.global _start
_start:

    @ Carregando numero 2
    LDR r0, =const_0    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 2
    LDR r0, =const_1    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: +
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VADD.F64 D2, D0, D1  @ D2 = A + B
    VPUSH {D2}           @ Empilhar resultado

    @ Carregando numero 5
    LDR r0, =const_2    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 3
    LDR r0, =const_3    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: -
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VSUB.F64 D2, D0, D1  @ D2 = A - B
    VPUSH {D2}           @ Empilhar resultado

    @ Carregando numero 4
    LDR r0, =const_4    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 3
    LDR r0, =const_5    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: *
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VMUL.F64 D2, D0, D1  @ D2 = A * B
    VPUSH {D2}           @ Empilhar resultado

    @ Carregando numero 8
    LDR r0, =const_6    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Carregando numero 2
    LDR r0, =const_7    @ Endereco do numero na RAM
    VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
    VPUSH {D0}           @ Empilhar na pilha RPN

    @ Operacao Matematica: /
    VPOP {D1}            @ B (Operando Direita)
    VPOP {D0}            @ A (Operando Esquerda)
    VDIV.F64 D2, D0, D1  @ D2 = A / B
    VPUSH {D2}           @ Empilhar resultado

fim:
    B fim

