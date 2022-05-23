#ifndef LIBC_H

#define LIBC_H
#include <stdint.h>
#include <syscalls.h>

#define MEM_DUMP_LEN 32
#define BASE_HEX 16

int strcmp(char * str1, char * str2);
int strlen(char * str);
int str_to_num(char * str);
uint64_t str_to_hex(char * str);
int is_valid_hex(char * str);
int num_to_str(unsigned long long num, char * buffer, int bufferSize);
int num_length(unsigned long long num);
void sleep(int seconds);

#endif