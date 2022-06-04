#include <scheduler.h>
#include <interrupts.h>
#include <naiveConsole.h>
#include <schedulerfunctions.h>

static task processes[NUM_PROCESSES];
static int process_qty = 0;
static int current_pid = -1;

// Cantidad de procesos en ACTIVE sin contar a while1
static int running_processes = 0;

static char in_split_screen = 0;
static char in_unique_screen = 0;

static char left_screen_suspended = 0;
static char right_screen_suspended = 0;
static char unique_screen_suspended = 0;

#define ACTIVE 2
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
            .status = PAUSED
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
    task new_task = {
        .rip = rip,
        .rsp = initialize_process(STACK_BASE + PROCESS_SIZE * process_qty, rip,fd,string),
        .stack_base = STACK_BASE + PROCESS_SIZE * process_qty,
        .status = ACTIVE
    };
    processes[process_qty++] = new_task;
    running_processes++;
    return process_qty - 1;
}

void current_process_returned() {
    update_status(current_pid, FINISHED);
    running_processes--;
    if (!in_split_screen) {
        process_qty--;
        set_in_unique_screen(0);
        update_status(2, ACTIVE);
        running_processes++;
    }
    current_pid = -1;
    scheduler();
}

//Guarda la current task a ejecutar, teniendo en cuenta el pid que recibe como argumento
//actualiza el current pid y corre el proceso
void exec_process(int pid){
    if ( pid < 0 || pid >= process_qty) {
        return;
    }
    task current_task = processes[pid];
    current_pid = pid;
    if (pid > 0) {
        current_task.status = ACTIVE;
    }
    processes[pid] = current_task;
    run_process(current_task.rsp);
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
    processes[pid] = current_task;
}

int hibernate_process(int pid) {
    if ( pid < 0 || pid >= process_qty ) {
        return 0;
    }
    pause_process(pid);
    update_status(pid, PAUSED);
    running_processes--;
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
    while (processes[next_pid_to_run].status < ACTIVE) {
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

int get_current_pid() {
    return current_pid;
}

void stop_split_screen() {
    set_in_split_screen(0);

    left_screen_suspended = 0;
    right_screen_suspended = 0;

    update_status(3, FINISHED);
    update_status(4, FINISHED);
    process_qty -= 2;

    update_status(2, ACTIVE);
    running_processes = 1;
    current_pid = -1;

    scheduler();
}

void kill_unique_process() {
    if(processes[3].status == FINISHED) {
        return;
    }
    ncNewline(2);
    set_in_unique_screen(0);
    update_status(3, FINISHED);

    // Esto lo hago por si quiero killear el programa cuando se encontraba
    // en pausa.
    if (running_processes) {
        running_processes--;
    }
    process_qty--;

    update_status(2, ACTIVE);
    running_processes++;
    current_pid = -1;
    unique_screen_suspended = 0;
    scheduler();
}

void suspend_unique_process(){
    if(processes[3].status == FINISHED) {
        return;
    }
    if(!unique_screen_suspended){
        unique_screen_suspended = 1;
        update_status(3, PAUSED);
        running_processes--;
    }else{
        unique_screen_suspended = 0;
        update_status(3, ACTIVE);
        running_processes++;
    }
    scheduler();
}

void suspend_left_split_screen() {
    if(processes[3].status == FINISHED) {
        return;
    }
    if(left_screen_suspended == 0){
        left_screen_suspended = 1;
        update_status(3, PAUSED);
        running_processes--;
    }else{
        left_screen_suspended = 0;
        update_status(3, ACTIVE);      
        running_processes++;
    }
    scheduler();
}

void suspend_right_split_screen() {
    if(processes[4].status == FINISHED) {
        return;
    }
    if(right_screen_suspended == 0){
        right_screen_suspended = 1;
        update_status(4, PAUSED);
        running_processes--;
    } else {
        right_screen_suspended = 0;
        update_status(4, ACTIVE);
        running_processes++;
    }
    scheduler();
}

void update_status(int pid, int status) {
    task the_task = processes[pid];
    the_task.status = status;
    processes[pid] = the_task;
}

void kill_split_process(int pid) {
    update_status(pid, FINISHED);
    running_processes--;
    scheduler();
}