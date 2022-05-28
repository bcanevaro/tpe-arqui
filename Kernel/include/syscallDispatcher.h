#ifndef SYSCALL_DISPATCHER_H

#define SYSCALL_DISPATCHER_H

typedef struct {
    //-1 si no se ingresa
    char * string;
    int integer;
}arguments;

int sys_write(unsigned int fd, const char * buf, unsigned int count);
int sys_read(unsigned int fd, char * buf, unsigned int count);
int sys_clear(uint64_t rdi, uint64_t rsi, uint64_t rdx);
int sys_seconds_elapsed(uint64_t rdi, uint64_t rsi, uint64_t rdx);
int sys_datetime(uint64_t * rdi, uint64_t rsi, uint64_t rdx);
int sys_print_byte_from_mem(unsigned int fd, uint8_t * address, uint64_t rdx);
int sys_start_split_screen(uint64_t functions[], arguments * args_f1, arguments * args_f2);

#endif
