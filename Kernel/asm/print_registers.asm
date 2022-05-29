GLOBAL load_registers
GLOBAL continue_execution
EXTERN main
EXTERN getStackBase
section .text

continue_execution:
    call getStackBase	        ; Get thet stack address
	mov rsp, rax			; Set up the stack with the returned address
	call main
 
 
    ; https://os.phil-opp.com/handling-exceptions/ 
    ; STACK
    ;	RBP     -> stack frame
    ;   RIP     -> dirección de retorno
    ;   r15
	;   r14
	;   r13
	;   r12
	;   r11
	;   r10
	;   r9
	;   r8
	;   rsi
	;   rdi
	;   rbp
	;   rdx
	;   rcx
	;   rbx
	;   rax
    ;   RIP     -> instruction that caused the exception -> this is pushed by the microproccesor
    ;   CS
    ;   RFLAGS
    ;   RSP
    ;   SS
load_registers:
    enter 0, 0

    mov rbx, 0

.loop:
    mov rax, [rbp+rbx+8]
    mov [registers+rbx], rax
    add rbx, 8
    cmp rbx, length
    jne .loop
    
    leave
    ret

section .data
    length equ 20*8

section .bss
    registers resq 20