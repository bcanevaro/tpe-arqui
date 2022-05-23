#ifndef SYSCALLS_H

#define SYSCALLS_H
#include <stdint.h>
int write(int fd, const char * buf, int count);
int read(int fd, char * buf, int count);
int clear_screen();
int seconds_elapsed();
int system_datetime(uint64_t * rdi, uint64_t rsi, uint64_t rdx);

#endif