UM: EQU 1
section text
rot: input n1
load n1
jmpz fim
store n2
add n3
store n2 + UM
output n2 + UM
jmp rot
fim: output n1
STOP
section data
n1: space
n2: space 3
n3: const 3
