GLOBAL write
GLOBAL read

section .text

; int write(int fd, const char * buf, int count)
write:
    enter 0, 0

    mov rax, 0x01
    int 80h
    
    leave
    ret

; int read(int fd, char * buf, int count)
read:
    enter 0, 0

    mov rax, 0x00
    int 80h
    
    leave
    ret