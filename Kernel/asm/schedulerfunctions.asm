GLOBAL initialize_process
GLOBAL run_process
GLOBAL stop_process

EXTERN current_process_returned

; uint64_t initialize_process(uint64_t stack_base, uint64_t rip, int fd, char * string);
initialize_process: 
    enter 0, 0 

    mov rsp, rdi
	mov qword [rsp], current_process_returned
	sub rsp, 8
    push 0x00   ; SS (Stack Segment)
    push rdi    ; RSP 
    push 0x200  ; Registro de flags. El 200 pone en 1 el flag de interrupcion.
    push 0x8    ; CS (Code Segment)    
    push rsi    ; RIP
	mov rdi,rdx ;le pasamos fd al primer argumento
	mov rsi,rcx ;le pasamos string al segundo argumento
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

; uint64_t stop_process(uint64_t current_rsp, uint64_t rip, uint64_t * current_gp_registers);
stop_process:
    enter 0, 0
    mov rsp, rdi
    push 0x00   ; SS (Stack Segment)
    push rdi    ; RSP 
    push 0x200  ; Registro de flags. El 200 pone en 1 el flag de interrupcion.
    push 0x8    ; CS (Code Segment)    
    push rsi    ; RIP
    ; Pusheamos todos los registros para guardar contexto
    push qword [rdx]
	push qword [rdx+8]
	push qword [rdx+16]
	push qword [rdx+24]
	push qword [rdx+32]
	push qword [rdx+40]
	push qword [rdx+48]
	push qword [rdx+56]
	push qword [rdx+64]
	push qword [rdx+72]
	push qword [rdx+80]
	push qword [rdx+88]
	push qword [rdx+96]
	push qword [rdx+104]
	push qword [rdx+112]
    ; Retornamos el SP (Stack Pointer)
    mov rax, rsp
    leave
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
    ; Desarma el stack de excepciones
    ; Retreived from https://os.phil-opp.com/returning-from-exceptions/exception-stack-frame.svg

	; signal pic EOI (End of Interrupt)
	; ESTO ES MUY NECESARIO PORQUE SINO NO VUELVE A ESCUCHAR A EL TECLADO PORQUE NUNCA TERMINA LA INTERRUPCION
	mov al, 20h
	out 20h, al

	pop rax
    iretq