GLOBAL load_registers
section .text
 
    ; https://os.phil-opp.com/handling-exceptions/ 
    ; STACK
    ;	RBP     -> stack frame
    ;   RIP     -> dirección de retorno
    ;   rax
	;   rbx
	;   rcx
	;   rdx
	;   rbp
	;   rdi
	;   rsi
	;   r8
	;   r9
	;   r10
	;   r11
	;   r12
	;   r13
	;   r14
	;   r15
    ;   RIP     -> instruction that caused the exception -> this is pushed by the microproccesor
    ;   CS
    ;   RFLAGS
    ;   RSP
    ;   SS
load_registers:
    enter 0, 0

    mov rbx, 0

.loop:
    mov rax, [rbp+rbx+16]
    mov [registers+rbx], rax
    add rbx, 8
    cmp rbx, length
    jne .loop
    
    mov rax, registers
    leave
    ret

section .data
    length equ 20*8

section .bss
    registers resq 20