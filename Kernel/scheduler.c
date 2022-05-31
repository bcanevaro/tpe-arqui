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
static char in_unique_screen = 0;

static char left_screen_suspended = 0;
static char right_screen_suspended = 0;
static char unique_screen_suspended = 0;

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

void load_dummy_process(){
    task while1_task = {
            .rip = &while1,
            .rsp = initialize_process(STACK_BASE, &while1, -1, -1),
            .stack_base = STACK_BASE,
            .active = PAUSED
        };
    processes[0] = while1_task;
}

// Cuando llamamos al pipe se tiene que ejecutar la siguiente funcion;
//Función que crea una task y la agrega al array processes
//devuelve el pid
int load_processes(uint64_t rip, int fd, char * string) {
    if (process_qty == 0) {
        load_dummy_process();
        process_qty++;
    }
    int found = 0;
    int i;
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
        load_dummy_process();
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

void set_in_unique_screen(char value) {
    in_unique_screen = value;
}

char get_in_unique_screen() {
    return in_unique_screen;
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

// Unique Screen Management Functions
void kill_unique_process(){
    task current_task_1 = processes[3];
    task current_task_2 = processes[4];
    if(current_task_1.active == FINISHED && current_task_1.active == FINISHED) {
        return;
    }
    ncClear();
    set_in_unique_screen(0);
    current_task_1.active = FINISHED;
    current_task_2.active = FINISHED;

    // Esto lo hago por si quiero killear el programa cuando se encontraba
    // en pausa.
    if(running_processes){
        running_processes--;
    }
    processes[3] = current_task_1;
    processes[4] = current_task_2;
    process_qty--;

    task terminal_task = processes[2];
    terminal_task.active = IDLE;
    processes[2] = terminal_task;
    running_processes++;
    current_pid = -1;
    unique_screen_suspended = 0;
    scheduler();
}

void suspend_unique_process(){
    if(processes[3].active < IDLE && processes[4].active < IDLE) {
        return;
    }
    if(!unique_screen_suspended){
        unique_screen_suspended = 1;
        pause_process(3);
        pause_process(4);
        task current_task = processes[3];
        current_task.active = PAUSED;
        task current_task_2 = processes[4];
        current_task_2.active = PAUSED;
        running_processes--;
        processes[3] = current_task;
        processes[4] = current_task_2;
        scheduler();
    }else{
        unique_screen_suspended = 0;
        task current_task = processes[3];
        current_task.active = IDLE;
        task current_task_2 = processes[4];
        current_task_2.active = IDLE;
        running_processes++;
        scheduler();
    }
}


// Para cada pantalla puedo tener lo siguiente:
//  * -1 si la killee
//  * 0 si esta funcionando, es decir, imprimiendo.
//  * 1 si esta pausada/suspendida.
// Algo importante que no me fije es que si el programa ya finalizo no deberia
// poder hacer nada con todas las F1, F2, ..., F6. Para Unique Screen esta realizado.
// MALISIMA
void kill_left_split_screen() {
    task current_task = processes[3];
    current_task.rip = get_current_rip();
    current_task.rsp = stop_process(get_current_rsp(), current_task.rip, get_current_gp_registers());
    current_task.active = PAUSED;
    processes[3] = current_task;
    running_processes--;
    scheduler();
}
// MAL
void suspend_left_split_screen() {
    if(left_screen_suspended == 0){
        left_screen_suspended = 1;
        task current_task = processes[3];
        current_task.rip = get_current_rip();
        current_task.rsp = stop_process(get_current_rsp(), current_task.rip, get_current_gp_registers());
        current_task.active = PAUSED;
        processes[3] = current_task;
        running_processes--;
        scheduler();
    }else{
        left_screen_suspended = 0;
        task task_left = processes[3];
        task_left.active = IDLE;
        processes[3] = task_left;      
        running_processes++;
        scheduler();
    }
}

void suspend_right_split_screen() {
}