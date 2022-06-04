#ifndef SYSCALL_DISPATCHER_H

#define SYSCALL_DISPATCHER_H

typedef struct {
    //-1 si no se ingresa
    int integer;
    char * string;
}arguments;

int sys_write(unsigned int fd, const char * buf, unsigned int count);
int sys_read(unsigned int fd, char * buf, unsigned int count);
int sys_clear(uint64_t rdi, uint64_t rsi, uint64_t rdx);
int sys_seconds_elapsed(uint64_t rdi, uint64_t rsi, uint64_t rdx);
int sys_datetime(uint64_t * rdi, uint64_t rsi, uint64_t rdx);
int sys_print_byte_from_mem(unsigned int fd, uint8_t * address, uint64_t rdx);
int sys_start_split_screen(uint64_t rdi, uint64_t rsi, uint64_t rdx);
int sys_load_process(uint64_t function, arguments * args_function, uint64_t rdx);
int sys_hibernate_process(int pid, uint64_t rsi, uint64_t rdx);
int sys_start_unique_screen(uint64_t rdi, uint64_t rsi, uint64_t rdx);
int sys_get_inforeg_regs(uint64_t ** result, uint64_t rsi, uint64_t rdx);

#endif
