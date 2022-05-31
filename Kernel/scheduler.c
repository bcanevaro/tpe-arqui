#include <scheduler.h>
#include <interrupts.h>
#include <naiveConsole.h>
#include <schedulerfunctions.h>

static task processes[NUM_PROCESSES];
static int process_qty = 0;
static int current_pid = -1;
static char scheduler_active = 0;

// Cantidad de procesos en IDLE o ACTIVE sin contar a while1
static int running_processes = 0;

static char in_split_screen = 0;

#define ACTIVE 2
#define IDLE 1
#define PAUSED 0
#define FINISHED -1

// El 0 es sampleCodeModule
// El 1 es while1
// El 2 es terminal
// 3 y 4 para procesos

void while1() {
    while (1);
}

// Cuando llamamos al pipe se tiene que ejecutar la siguiente funcion;
//Función que crea una task y la agrega al array processes
//devuelve el pid
int load_processes(uint64_t rip, int fd, char * string) {
    if (process_qty == 0) {
        task while1_task = {
            .rip = &while1,
            .rsp = initialize_process(STACK_BASE + PROCESS_SIZE * process_qty, &while1, -1, -1),
            .stack_base = STACK_BASE + PROCESS_SIZE * process_qty,
            .active = PAUSED
        };
        processes[process_qty++] = while1_task;
    }
    int found = 0;
    int i;
    for(i = 3; i < process_qty && !found; i++){
        if(processes[i].active == FINISHED){
            found = 1;
        }
    }
    if(!found){
        task new_task = {
            .rip = rip,
            .rsp = initialize_process(STACK_BASE + PROCESS_SIZE * process_qty, rip,fd,string),
            .stack_base = STACK_BASE + PROCESS_SIZE * process_qty,
            .active = IDLE
        };
        processes[process_qty++] = new_task;
        running_processes++;
        return process_qty - 1;
    }
}

void current_process_returned() {
    task current_task = processes[current_pid];
    current_task.active = FINISHED;
    running_processes--;
    processes[current_pid] = current_task;
    if (!in_split_screen) {
        process_qty--;
        if (process_qty <= 3) {
            task terminal_task = processes[2];
            terminal_task.active = IDLE;
            processes[2] = terminal_task;
            running_processes++;
        }
    }
    current_pid = -1;
    scheduler();
}

//Guarda la current task a ejecutar, teniendo en cuenta el pid que recibe como argumento
//actualiza el current pid y corre el proceso
//Si terminó de correr el proceso el lugar en el array que guarda los procesos eliminado
//y actualizar el valor de current pid a -1 para saber que no se está corriendo nada
void exec_process(int pid){
    if ( pid < 0 || pid >= process_qty) {
        return;
    }
    task current_task = processes[pid];
    current_pid = pid;
    if (pid > 0) {
        current_task.active = ACTIVE;
    }
    processes[pid] = current_task;
    run_process(current_task.rsp);
    // //Si llego aca, es porque el proceso terminó
    // current_task.active = FINISHED;
    // processes[pid] = current_task;
    // current_pid = -1;
}

//Obtiene el proceso de acuerdo al pid recibido por argumento
//y realiza la actualizacion de RIP y RSP de la task
void pause_process(int pid) {
    if ( pid < 0 || pid >= process_qty ) {
        return;
    }
    task current_task = processes[pid];
    current_task.rip = get_current_rip();
    current_task.rsp = stop_process(get_current_rsp(), current_task.rip, get_current_gp_registers());
    if (pid > 0) {
        current_task.active = IDLE;
    }
    processes[pid] = current_task;
}

// void activate_scheduler() {
//     scheduler_active = 1;
// }

// char is_scheduler_active() {
//     return scheduler_active;
// }

int hibernate_process(int pid){
    if ( pid < 0 || pid >= process_qty ) {
        return 0;
    }
    pause_process(pid);
    task current_task = processes[pid];
    current_task.active = PAUSED;
    running_processes--;
    processes[pid] = current_task;
    exec_process(pid+1);
    return 1;
}

void scheduler(){
    if(process_qty <= 1){
        return;
    }
    pause_process(current_pid);
    if (running_processes == 0) {
        exec_process(0);
    }
    int next_pid_to_run = (current_pid + 1) % process_qty;
    while (processes[next_pid_to_run].active == FINISHED || processes[next_pid_to_run].active == PAUSED) {
        next_pid_to_run = (next_pid_to_run + 1) % process_qty;
    }
    exec_process(next_pid_to_run);
}

void set_in_split_screen(char value) {
    in_split_screen = value;
}

char get_in_split_screen() {
    return in_split_screen;
}

void stop_split_screen() {
    set_in_split_screen(0);

    task task_left = processes[3];
    task_left.active = FINISHED;
    processes[3] = task_left;
    task task_right = processes[4];
    task_right.active = FINISHED;
    processes[4] = task_right;

    process_qty -= 2;
    task terminal_task = processes[2];
    terminal_task.active = IDLE;
    processes[2] = terminal_task;

    running_processes = 1;
    current_pid = -1;
    scheduler();
}
