#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include <stdint.h>
#define NUM_PROCESSES 2
// Puntero a funcion
typedef void (*function)(int);

// Estructura que contiene el contexto de la funcion cuando se corre
typedef struct {
    uint64_t stack_base;
    uint64_t rip; //RIP cuando se corta la funcion
    uint64_t rsp; //RIP cuando se corta la funcion
} task;

static task processes[NUM_PROCESSES];

uint64_t initialize_process(uint64_t stack_base, uint64_t rip);
uint64_t stop_process(uint64_t current_rsp, uint64_t rip);
uint64_t get_rsp();
void run_process(uint64_t rsp);

#endif