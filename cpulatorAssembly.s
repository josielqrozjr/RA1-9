.global _start
.text
_start:
@ Carregando numero 3.14
LDR r0, =const_0    @ Endereco do numero na RAM
VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
VPUSH {D0}           @ Empilhar na pilha RPN
@ Operacao Matematica
VPOP {D1}            @ B (Operando Direita)
VPOP {D0}            @ A (Operando Esquerda)
VADD.F64 D2, D0, D1  @ D2 = A + B
VPUSH {D2}           @ Empilhar resultado
@ Carregando numero 2.0
LDR r0, =const_1    @ Endereco do numero na RAM
VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
VPUSH {D0}           @ Empilhar na pilha RPN
@ Operacao Matematica
VPOP {D1}            @ B (Operando Direita)
VPOP {D0}            @ A (Operando Esquerda)
VADD.F64 D2, D0, D1  @ D2 = A + B
VPUSH {D2}           @ Empilhar resultado
@ Carregando numero 10.5
LDR r0, =const_2    @ Endereco do numero na RAM
VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
VPUSH {D0}           @ Empilhar na pilha RPN
@ Salvando na memoria: CONTADOR
VPOP {D0}            @ Desempilhar o resultado
LDR r0, =var_CONTADOR      @ Capturar endereco da variavel
VSTR.F64 D0, [r0]    @ Salvar na RAM
@ Carregando numero 4
LDR r0, =const_3    @ Endereco do numero na RAM
VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
VPUSH {D0}           @ Empilhar na pilha RPN
@ Operacao Matematica
VPOP {D1}            @ B (Operando Direita)
VPOP {D0}            @ A (Operando Esquerda)
VDIV.F64 D2, D0, D1  @ D2 = A / B
VPUSH {D2}           @ Empilhar resultado
@ Carregando numero 0
LDR r0, =const_4    @ Endereco do numero na RAM
VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
VPUSH {D0}           @ Empilhar na pilha RPN
@ Operacao Matematica
VPOP {D1}            @ B (Operando Direita)
VPOP {D0}            @ A (Operando Esquerda)
VDIV.F64 D2, D0, D1  @ D2 = A / B
VPUSH {D2}           @ Empilhar resultado
@ Carregando numero 2
LDR r0, =const_5    @ Endereco do numero na RAM
VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
VPUSH {D0}           @ Empilhar na pilha RPN
@ Operacao Matematica
VPOP {D1}            @ B (Operando Direita)
VPOP {D0}            @ A (Operando Esquerda)
VADD.F64 D2, D0, D1  @ D2 = A + B
VPUSH {D2}           @ Empilhar resultado
@ Carregando numero 2
LDR r0, =const_6    @ Endereco do numero na RAM
VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
VPUSH {D0}           @ Empilhar na pilha RPN
@ Carregando numero 2
LDR r0, =const_7    @ Endereco do numero na RAM
VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
VPUSH {D0}           @ Empilhar na pilha RPN
@ Carregando numero 2
LDR r0, =const_8    @ Endereco do numero na RAM
VLDR.F64 D0, [r0]    @ Carregar valor 64-bits para D0
VPUSH {D0}           @ Empilhar na pilha RPN
@ Operacao Matematica
VPOP {D1}            @ B (Operando Direita)
VPOP {D0}            @ A (Operando Esquerda)
VADD.F64 D2, D0, D1  @ D2 = A + B
VPUSH {D2}           @ Empilhar resultado
fim:
    B fim

