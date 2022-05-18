
GLOBAL write

section .text

; int write(int fd, const char * buf, int count)
write:
    enter 0, 0

    mov rax, 0x01
    int 80h
    
    leave
    ret