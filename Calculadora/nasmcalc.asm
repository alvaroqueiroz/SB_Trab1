; ----------------------------------------------------------------------------------------
; Progam executes 5 math operations with integers. Runs on 32-bit Linux.
; To assemble and run:
;
;     nasm -felf nasmcalc.asm && ld nasmcalc.o && ./a.out
; ----------------------------------------------------------------------------------------

global      _start

            section   .text
_start:     call      menu
            call      switch_case
			


exit:       mov       eax, 0x00000001         ; system call for exit
            xor       ebx, ebx                ; exit code 0
            int 80H                           ; invoke operating system to exit


; prints the menu
menu:       mov ecx, message1				; "Por favor escreva seu nome", 13, 10
			mov edx, mess1_len
			call puts

            mov	ecx, name
            mov edx, 60
            call gets

            mov ecx, message2				; "Hola, "
            mov edx, mess2_len
            call puts

            mov ecx, name					; name from input
            mov edx, 60
            call puts

            mov ecx, message3				; ", bem-vindo ao programa de CALC-IA32", 13, 10
            mov edx, mess3_len
            call puts

			mov ecx, menu0					; "ESCOLHA UMA OPCAO:", 13, 10
			mov edx, menu0_len
			call puts
			
			mov ecx, menu1					; "- 1: SOMA", 13, 10
			mov edx, menu1_len
			call puts
			
			mov ecx, menu2					; "- 2: SUBTRACAO", 13, 10
			mov edx, menu2_len
			call puts
			
			mov ecx, menu3					; "- 3: MULTIPLICACAO", 13, 10
			mov edx, menu3_len
			call puts
			
			mov ecx, menu4					; "- 4: DIVISAO", 13, 10
			mov edx, menu4_len
			call puts
			
			mov ecx, menu5					; "- 5: MOD", 13, 10
			mov edx, menu5_len
			call puts
			
			mov ecx, menu6					; "- 6: SAIR", 13, 10
			mov edx, menu6_len
			call puts
			
            ret

; selects menu option
switch_case:
			mov  ecx, case_menu
            mov  edx, 1
			call gets

            mov eax, [case_menu]
            cmp eax, '1'
            je case1
            cmp eax, '2'
            je case2
            cmp eax, '3'
            je case3
            cmp eax, '4'
            je case4
            cmp eax, '5'
            je case5
            cmp eax, '6'
            je case6
            jmp deft

case1:
            call arg_input
            call op_sum
            call res_output
            ret
case2:
            call arg_input
            call op_sub
            call res_output
            ret
case3:
            call arg_input
            call op_mul
            call res_output
            ret
case4:
            call arg_input
            call op_div
            call res_output
            ret
case5:
            call arg_input
            call op_mod
            call res_output
            ret
case6:
deft:
            jmp exit


arg_input:
			mov ecx, arg1
			mov edx, 1
			call gets
			
            mov ecx, message4				; "Insira o primeiro argumento:", 13, 10
            mov edx, mess4_len
            call puts
			
			mov ecx, 10
			copy1:
				mov ebx, arg1
				add ebx, ecx
				mov al, [ebx]
				mov ebx, argumento
				add ebx, ecx
				mov [ebx], al
			loop copy1
			mov ebx, [int1]
			mov [inteiro], ebx
            call get_args
			
			mov ecx, message5				; "Insira o segundo argumento:", 13, 10
            mov edx, mess5_len
            call puts
			
			mov ecx, 10
			copy2:
				mov ebx, arg2
				add ebx, ecx
				mov al, [ebx]
				mov ebx, argumento
				add ebx, ecx
				mov [ebx], al
			loop copy2
			mov ebx, [int2]
			mov [inteiro], ebx
            call get_args
            ret

res_output:
			mov ecx, message6
			mov edx,mess6_len
			call puts	
				
			
			mov eax, [resint]
			;mov eax, [int1]
			cmp eax, 0
			jge next2
			neg eax
			
			
			next2:
			mov ebx, 10
			cdq
			idiv ebx
			add edx, 30H
			mov ecx, resstring
			add ecx, 10
			mov [ecx], dl
			cdq
			idiv ebx
			add edx, 30H
			mov ecx, resstring
			add ecx, 9
			mov [ecx], dl
			cdq
			idiv ebx
			add edx, 30H
			mov ecx, resstring
			add ecx, 8
			mov [ecx], dl
			cdq
			idiv ebx
			add edx, 30H
			mov ecx, resstring
			add ecx, 7
			mov [ecx], dl
			cdq
			idiv ebx
			add edx, 30H
			mov ecx, resstring
			add ecx, 6
			mov [ecx], dl
			cdq
			idiv ebx
			add edx, 30H
			mov ecx, resstring
			add ecx, 5
			mov [ecx], dl
			cdq
			idiv ebx
			add edx, 30H
			mov ecx, resstring
			add ecx, 4
			mov [ecx], dl
			cdq
			idiv ebx
			add edx, 30H
			mov ecx, resstring
			add ecx, 3
			mov [ecx], dl
			cdq
			idiv ebx
			add edx, 30H
			mov ecx, resstring
			add ecx, 2
			mov [ecx], dl
			cdq
			idiv ebx
			add edx, 30H
			mov ecx, resstring
			add ecx, 1
			mov [ecx], dl				
			mov ecx, resstring
			add ecx, 11
			mov [ecx], byte 13
			mov ecx, resstring
			add ecx, 12
			mov [ecx], byte 10
			
			mov eax, [resint]
			cmp eax, 0
			jl plus_sign
			mov [resstring], byte '-'
			jmp next
			plus_sign:
			mov [resstring], byte '+'
			next: 
						
			mov ecx, resstring
			mov edx, 13
			
			call puts
				
				
			ret
			
			
			
op_sum:
			mov eax, [int1]
			mov ebx, [int2]
			add eax, ebx
			mov [resint], eax
			ret
			
op_sub:
			mov eax, [int1]
			mov ebx, [int2]
			sub eax, ebx
			mov [resint], eax			
			ret
op_mul:
			mov eax, [int1]
			mov ebx, [int2]
			imul ebx
			mov [resint], eax						
			ret
op_div:
			mov eax, [int1]
			mov ebx, [int2]
			idiv ebx
			mov [resint], eax
			ret
op_mod:
			mov eax, [int1]
			mov ebx, [int2]
			idiv ebx
			mov [resint], edx
            ret
            
; prints string in std out
puts:		mov eax, 0x00000004			; sys_write code
			mov ebx, 1					; std out
			int 80H						; syscall
			ret							; return

; get string from std in
gets:		mov eax, 0x00000003			; sys_read code
			mov ebx, 1					; std in
			int 80H						; syscall
			ret							; return


; get signed int from std in
get_args:
			mov	ecx, argumento
            mov edx, 11
            call gets
			
			xor ecx, ecx
			count:
				mov eax, [argumento + ecx]
				inc ecx
				cmp eax, 0
				jne count
			sub ecx, 3
			
			;add ecx, 30H
			;push ecx
			;mov ecx, esp
			;mov edx, 1
			;call puts
			;pop edx
			;mov ecx, argumento
			;call puts
			;mov ecx, edx
			;sub ecx, 30h
			

			mov eax, 1
			atoi:
				mov [temp], eax	
				mov ebx, argumento
				add ebx, ecx
				mov ebx, [ebx]
				sub ebx, 30H
				imul ebx
				add [inteiro], eax
				mov eax, [temp]
				imul eax, eax, 10
				sub ecx, 1
				test ecx, 1
				jne atoi

			cmp [argumento], dword '-'
			jne positive
			negative:
				neg dword [inteiro]
				jmp fim
			positive:
				cmp [argumento], dword '+'
				je fim
			unsigned:
				mov ebx, [argumento + ecx]
				sub ebx, 30H
				imul ebx
				add [inteiro], eax
			fim:
			ret

debugmess:	
			pushad
			mov ecx, dbgmss
			mov edx, dbglen
			call puts
			popad
			ret




section     .data
message1:   db			"Por favor escreva seu nome", 13, 10      ;newline at the end
mess1_len:	equ			$-message1
message2:   db			"Hola, "
mess2_len:	equ			$-message2
message3:   db			", bem-vindo ao programa de CALC-IA32", 13, 10
mess3_len:	equ			$-message3
menu0:      db			"ESCOLHA UMA OPCAO:", 13, 10
menu0_len:	equ			$-menu0
menu1:      db			"- 1: SOMA", 13, 10
menu1_len:	equ			$-menu1
menu2:      db			"- 2: SUBTRACAO", 13, 10
menu2_len:	equ			$-menu2
menu3:      db			"- 3: MULTIPLICACAO", 13, 10
menu3_len:	equ			$-menu3
menu4:      db			"- 4: DIVISAO", 13, 10
menu4_len:	equ			$-menu4
menu5:      db			"- 5: MOD", 13, 10
menu5_len:	equ			$-menu5
menu6:      db			"- 6: SAIR", 13, 10
menu6_len	equ			$-menu6
message4:   db			"Insira o primeiro argumento:", 13, 10
mess4_len:	equ			$-message4
message5:   db			"Insira o segundo argumento:", 13, 10
mess5_len:	equ			$-message5
message6	db			"O resultado e: "
mess6_len	equ			$-message6
dbgmss		db			"debug!", 13, 10
dbglen		equ			$-dbgmss



section	.bss

name:		resb	60
case_menu:	resd	1
arg1:		resb	11
arg2:		resb	11
int1:		resd	1
int2:		resd	1
resstring:	resb	13
resint:		resd	1
temp:		resd	1
argumento:  resb	11
inteiro:	resd	1
