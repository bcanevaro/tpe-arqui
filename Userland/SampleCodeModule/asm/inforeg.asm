GLOBAL inforeg
EXTERN print_regs

section .text

inforeg:
    ; No se arma el stackframe para no perder rbp.
    ; De igual manera, no se usa el stack.

    mov [registers], rax
    mov [registers+8], rbx
    mov [registers+16], rcx
    mov [registers+24], rdx
    mov [registers+32], rbp
    mov [registers+40], rdi
    mov [registers+48], rsi
    mov [registers+56], rsp
    mov [registers+64], r8
    mov [registers+72], r9
    mov [registers+80], r10
    mov [registers+88], r11
    mov [registers+96], r12
    mov [registers+104], r13
    mov [registers+112], r14
    mov [registers+120], r15

    mov rsi, registers
    call print_regs

    ret

section .bss
registers resq 16