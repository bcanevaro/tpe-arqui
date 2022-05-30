#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include <stdint.h>
#include <schedulerfunctions.h>
#define NUM_PROCESSES 4
#define STACK_BASE 0x450000
#define PROCESS_SIZE ( 8 * 1024 )
// Puntero a funcion
typedef void (*function)(int);

// Estructura que contiene el contexto de la funcion cuando se corre
typedef struct {
    uint64_t stack_base;
    uint64_t rip; //RIP cuando se corta la funcion
    uint64_t rsp; //RIP cuando se corta la funcion
    char active;
} task;


int load_processes(uint64_t rip, int fd, char * string);
void exec_process(int pid);
void scheduler(void);
void activate_scheduler(void);
char is_scheduler_active(void);
int hibernate_process(int pid);

#endif