#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include <stdint.h>
#include <schedulerfunctions.h>

#define NUM_PROCESSES 5
#define STACK_BASE 0x450000
#define PROCESS_SIZE ( 8 * 1024 )

// Estructura que contiene el contexto de la funcion cuando se corre
typedef struct {
    uint64_t stack_base;
    uint64_t rip; //RIP cuando se corta la funcion
    uint64_t rsp; //RIP cuando se corta la funcion
    char status;
} task;

// Task/Process Management
int load_processes(uint64_t rip, int fd, char * string);
void exec_process(int pid);
void scheduler(void);
int hibernate_process(int pid);

// Screen Management
void set_in_split_screen(char value);
char get_in_split_screen();
void set_in_unique_screen(char value);
char get_in_unique_screen();

// Screen Kill/Resume-Pause
void kill_unique_process();
void suspend_unique_process();
void suspend_left_split_screen();
void suspend_right_split_screen();

// Split Screen Kill/Resume-Pause
void stop_split_screen();

void update_status(int pid, int status);

int get_current_pid();
void kill_split_process(int pid);

#endif