#ifndef SYSCALLS_H

#define SYSCALLS_H
#include <stdint.h>

typedef struct {
    //-1 si no se ingresa
    int integer;
    char * string;
}arguments;

int write(int fd, const char * buf, int count);
int read(int fd, char * buf, int count);
int clear_screen();
int seconds_elapsed();
int system_datetime(uint64_t * info);
int print_byte_from_mem(unsigned int fd, uint8_t * address);
int start_split_screen();
int start_unique_screen();
int load_process(uint64_t function, arguments * args_function);
int hibernate_process(int pid);
int get_inforeg_regs(uint64_t ** results);

#endif