GLOBAL print_registers
GLOBAL continue_execution
EXTERN ncPrintColorful
EXTERN printRegisterFormat
EXTERN ncColorfulNewline
EXTERN ncNewline
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
    ;   RIP     -> calling function 
    ;   what we pushed
    ;   RIP     -> instruction that caused the exception -> this is pushed by the microproccesor
    ;   CS
    ;   RFLAGS
    ;   RSP
    ;   SS
print_registers:
    enter 0, 0

    call ncNewline
    mov rdi, separator
    mov rsi, red_color
    mov rdx, white_color
    call ncPrintColorful
    mov rdi, white_color
    call ncColorfulNewline
    mov rbx, 0

.loop:
    mov rdi, [registers+rbx]
    mov rsi, red_color
    mov rdx, white_color
    call ncPrintColorful
    add rbx, 8
    mov rdi, [rbp+rbx+8]
    call printRegisterFormat
    mov rdi, white_color
    call ncColorfulNewline
    cmp rbx, length
    jne .loop
    
    mov rdi, separator
    mov rsi, red_color
    mov rdx, white_color
    call ncPrintColorful
    mov rdi, white_color
    call ncColorfulNewline
    leave
    ret

section .data
    white_color equ 0x0F
    red_color equ 0x04
    separator db "---------------------", 0
    segmentSS db "     SS = ", 0
    rflags db " RFLAGS = ", 0
    segmentCS db "     CS = ", 0
    registerRIP db "    RIP = ", 0
    registerRAX db "    RAX = ", 0
    registerRBX db "    RBX = ", 0
    registerRCX db "    RCX = ", 0
    registerRDX db "    RDX = ", 0
    registerRBP db "    RBP = ", 0
    registerRDI db "    RDI = ", 0
    registerRSI db "    RSI = ", 0
    registerRSP db "    RSP = ", 0
    registerR8 db  "     R8 = ", 0
    registerR9 db  "     R9 = ", 0
    registerR10 db "    R10 = ", 0
    registerR11 db "    R11 = ", 0
    registerR12 db "    R12 = ", 0
    registerR13 db "    R13 = ", 0
    registerR14 db "    R14 = ", 0
    registerR15 db "    R15 = ", 0
    registers dq registerRAX, registerRBX, registerRCX, registerRDX, registerRBP, registerRDI, registerRSI, registerR8, registerR9, registerR10, registerR11, registerR12, registerR13, registerR14, registerR15, registerRIP, segmentCS, rflags, registerRSP, segmentSS
    length equ $-registers