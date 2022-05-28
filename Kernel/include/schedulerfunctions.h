#ifndef SCHEDULERFUNCTIONS_H
#define SCHEDULERFUNCTIONS_H

#include <stdint.h>

uint64_t initialize_process(uint64_t stack_base, uint64_t rip, int fd, char * string);
uint64_t stop_process(uint64_t current_rsp, uint64_t rip);
void run_process(uint64_t rsp);
#endif