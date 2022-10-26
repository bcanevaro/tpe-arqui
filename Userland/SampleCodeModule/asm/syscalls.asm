GLOBAL write
GLOBAL read
GLOBAL clear_screen
GLOBAL seconds_elapsed
GLOBAL system_datetime
GLOBAL print_byte_from_mem
GLOBAL start_split_screen
GLOBAL load_process
GLOBAL hibernate_process
GLOBAL start_unique_screen
GLOBAL get_inforeg_regs
GLOBAL move
GLOBAL miliseconds_elapsed


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

print_byte_from_mem:
    enter 0, 0

    mov rax, 0x05
    int 80h

    leave
    ret

start_split_screen:
    enter 0, 0

    mov rax, 0x06
    int 80h

    leave
    ret

load_process:
    enter 0, 0

    mov rax, 0x07
    int 80h

    leave
    ret

hibernate_process:
    enter 0, 0

    mov rax, 0x08
    int 80h

    leave
    ret

start_unique_screen:
    enter 0, 0

    mov rax, 0x09
    int 80h

    leave
    ret

get_inforeg_regs:
    enter 0, 0

    mov rax, 0x0a
    int 80h

    leave
    ret

move:
    enter 0,0

    mov rax,0x0b
    int 80h

    leave
    ret
miliseconds_elapsed:
    enter 0,0

    mov rax,0x0c
    int 80h

    leave
    ret