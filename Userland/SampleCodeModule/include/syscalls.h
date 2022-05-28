#ifndef SYSCALLS_H

#define SYSCALLS_H
#include <stdint.h>

typedef struct {
    //-1 si no se ingresa
    char * string;
    int integer;
}arguments;

int write(int fd, const char * buf, int count);
int read(int fd, char * buf, int count);
int clear_screen();
int seconds_elapsed();
int system_datetime(uint64_t * info);
int print_byte_from_mem(unsigned int fd, uint8_t * address);
int start_split_screen(uint64_t functions[], arguments * args_f1, arguments * args_f2);

#endif