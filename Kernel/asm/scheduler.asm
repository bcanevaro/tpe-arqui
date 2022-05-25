GLOBAL initizalize_process
GLOBAL get_rsp
GLOBAL run_process
GLOBAL stop_process

; uint64_t initialize_process(uint64_t stack_base, uint64_t rip);
initialize_process: 
    enter 0, 0 

    mov rsp, rdi
    push 0x00   ; SS (Stack Segment)
    push rdi    ; RSP 
    push 0x200  ; Registro de flags. El 200 pone en 1 el flag de interrupcion.
    push 0x8    ; CS (Code Segment)    
    push rsi    ; RIP
    ; Pusheamos todos los registros para guardar contexto
    push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
    ; Retornamos el SP (Stack Pointer)
    mov rax, rsp

    leave
    ret

; uint64_t stop_process(uint64_t current_rsp, uint64_t rip);
stop_process:
    enter 0, 0
    call initialize_process
    leave
    ret


; uint64_t get_rsp();
get_rsp: 
    mov rax, rsp
    ret

; void run_process(uint64_t rsp);
run_process:
    ; Devolvemos el RSP a su lugar para correr el programa desde donde estaba
    mov rsp, rdi
    ; Popeamos todos los registros a sus contextos correspondientes.
    pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
    ; Desarma el stack de excepciones
    ; https://os.phil-opp.com/returning-from-exceptions/exception-stack-frame.svg
    iretq