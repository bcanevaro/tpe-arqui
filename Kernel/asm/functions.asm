GLOBAL rtc_hours
GLOBAL rtc_minutes
GLOBAL rtc_seconds
GLOBAL rtc_bd_to_binary
GLOBAL kb_flag
GLOBAL get_key
GLOBAL read_port

section .text

rtc_bd_to_binary:
	push rbp
	mov rbp, rsp

	; Obtenemos los datos del registro OBh con el fin de cambiar
	; como se muestra la hora. Hasta el momento te lo da en BD, pero
	; la quiero en binario.
	; Copiamos en al la dir OBh para ingresar al registro
	; RTC Status register B.
	mov al, 0Bh 
	; Copiamos en la direccion 70h el 0Bh para poder acceder al registro
	; RTC Status register B.
	out 70h, al  
	; Hacemos la lectura del registro y la guardamos en al.
	in al, 71h
	; Creacion de la mascara para poner en 1 el bit 2 (tercero)
	; para leer en binario.
	mov bl, 4h
	or al, bl
	; Guardamos el cambio en bl.
	mov bl, al
	; Movemos a al 0Bh para poder volver a acceder al registro
	; RTC Status register B.
	mov al, 0Bh
	; Copiamos en la direccion 70h el 0Bh para poder acceder al registro
	; RTC Status register B. 
	out 70h, al
	; Movemos a al el cambio que queremos ingresar.
	mov al, bl
	; Para poder escribir en el registro usamos out.
	out 71h, al

	mov rsp, rbp
	pop rbp
	ret

rtc_hours:
	; Armado del StackFrame
	push rbp
	mov rbp, rsp
	
	call rtc_bd_to_binary

	; Finalmente obtenemos la hora en binario
	mov al, 04h
	out 70h, al
	in al, 71h
	
	; Desarmado del StackFrame
	mov rsp, rbp
	pop rbp
	ret

rtc_minutes:
	; Armado del StackFrame
	push rbp
	mov rbp, rsp

	call rtc_bd_to_binary

	; Finalmente obtenemos los minutos en binario
	mov al, 02h
	out 70h, al
	in al, 71h
	
	; Desarmado del StackFrame
	mov rsp, rbp
	pop rbp
	ret

rtc_seconds:
	; Armado del StackFrame
	push rbp
	mov rbp, rsp

	call rtc_bd_to_binary

	; Finalmente obtenemos la hora en binario
	mov al, 00h
	out 70h, al
	in al, 71h
	
	; Desarmado del StackFrame
	mov rsp, rbp
	pop rbp
	ret

get_key:
	; Armado del StackFrame
	push rbp
	mov rbp, rsp



	; Desarmado del StackFrame
	mov rsp, rbp
	pop rbp
	ret	

kb_flag:
	; Armado del StackFrame
	push rbp
	mov rbp, rsp
      
	; Ponemos un 0 en rax
	mov rax,0
loop:
	; Ponemos en el registro al un 0x64
	; Es el registro para poder leer en el mapa de entrada y salida
	in al,0x64       
	; Copiamos en cl lo que nos dio al
	mov cl,al
	; Hacemos al and 0x01 para mantener solamente el primer bit
	; con su valor
	and al,0x01   
	; Hacemos un compare entre al y 0    
	cmp al,0
	; Si el ultimo bit que paso por la mascara es cero entonces
	; sigo esperando porque vuelvo a saltar a loop
	je loop
	; Cuando se setea en 1 el bit 0 del 8042 Status Register
	; hago un mov (in) del registro 0x60 a al
	in al,0x60

	; Desarmado del StackFrame
	mov rsp, rbp
	pop rbp
	ret

read_port:
	push rbp
	mov rbp, rsp
	mov dx, di
	in al, dx
	mov rsp, rbp
	pop rbp 
	ret