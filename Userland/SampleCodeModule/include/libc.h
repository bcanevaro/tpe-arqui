#ifndef LIBC_H

#define LIBC_H
#include <stdint.h>
#include <syscalls.h>

#define MEM_DUMP_LEN 32

int strcmp(char * str1, char * str2);
int strlen(char * str);
int str_to_num(char * str);
uint64_t str_to_hex(char * str);
int is_valid_hex(char * str);
int num_to_str(unsigned long long num, char * buffer, int bufferSize);
int num_length(unsigned long long num);
void sleep(int seconds);
void sleepMiliseconds(int miliseconds);
void flush_buffer();
uint32_t uint_to_base(uint64_t value, char * buffer, uint32_t base);

#endif