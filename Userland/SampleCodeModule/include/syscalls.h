#ifndef SYSCALLS_H

#define SYSCALLS_H
#include <stdint.h>
int write(int fd, const char * buf, int count);
int read(int fd, char * buf, int count);
int clear_screen();
int seconds_elapsed();
int system_datetime(uint64_t * info);
int print_byte_from_mem(uint8_t * address);

#endif