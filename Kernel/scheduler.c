#include <scheduler.h>


// Cuando llamamos al pipe se tiene que ejecutar la siguiente funcion;
void load_processes(task p1, task p2) {
    processes[0] = p1;
    processes[1] = p2;
    processes[0]->sp = init_process(processes[0]->stack_base, processes[0]->ip);
    processes[1]->sp = init_process(processes[1]->stack_base, processes[1]->ip);
}


void scheduler(){
    
}
