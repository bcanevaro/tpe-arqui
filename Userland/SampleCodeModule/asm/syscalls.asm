GLOBAL write
GLOBAL read
GLOBAL clear_screen
GLOBAL seconds_elapsed
GLOBAL system_datetime

section .text

; int read(int fd, char * buf, int count)
read:
    enter 0, 0

    mov rax, 0x00
    int 80h
    
    leave
    ret

; int write(int fd, const char * buf, int count)
write:
    enter 0, 0

    mov rax, 0x01
    int 80h
    
    leave
    ret

clear_screen:
    enter 0, 0

    mov rax, 0x02
    int 80h

    leave
    ret

seconds_elapsed:
    enter 0, 0

    mov rax, 0x03
    int 80h

    leave
    ret

system_datetime:
    enter 0, 0

    mov rax, 0x04
    int 80h

    leave
    ret