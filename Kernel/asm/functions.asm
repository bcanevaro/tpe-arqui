GLOBAL rtc_hours
GLOBAL rtc_minutes
GLOBAL rtc_seconds
GLOBAL rtc_bd_to_binary
GLOBAL read_port
GLOBAL rtc_day
GLOBAL rtc_month
GLOBAL rtc_year

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

rtc_day:
	; Armado del StackFrame
	push rbp
	mov rbp, rsp

	call rtc_bd_to_binary

	; Finalmente obtenemos la hora en binario
	mov al, 07h
	out 70h, al
	in al, 71h
	
	; Desarmado del StackFrame
	mov rsp, rbp
	pop rbp
	ret

rtc_month:
	; Armado del StackFrame
	push rbp
	mov rbp, rsp

	call rtc_bd_to_binary

	; Finalmente obtenemos la hora en binario
	mov al, 08h
	out 70h, al
	in al, 71h
	
	; Desarmado del StackFrame
	mov rsp, rbp
	pop rbp
	ret

rtc_year:
	; Armado del StackFrame
	push rbp
	mov rbp, rsp

	call rtc_bd_to_binary

	; Finalmente obtenemos la hora en binario
	mov al, 09h
	out 70h, al
	in al, 71h
	
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