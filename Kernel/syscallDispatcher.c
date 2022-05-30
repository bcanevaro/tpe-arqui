#include <timer.h>
#include <stdint.h>
#include <naiveConsole.h>
#include <defs.h>
#include <keyboard.h>
#include <syscallDispatcher.h>
#include <functions.h>
#include <scheduler.h>

typedef int (*sys_call)(unsigned int, char *, unsigned int);
static sys_call system_call[] = {&sys_read, &sys_write, &sys_clear, &sys_seconds_elapsed, &sys_datetime, &sys_print_byte_from_mem, &sys_start_split_screen, &sys_load_process, &sys_hibernate_process};

typedef uint8_t (*rtc_argument)(void);
static rtc_argument realtime[] = {&rtc_seconds, &rtc_minutes, &rtc_hours, &rtc_day, &rtc_month, &rtc_year};

int syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t syscall_number) {
	return system_call[syscall_number](rdi, rsi, rdx);
}

int sys_write(unsigned int fd, const char * buf, unsigned int count) {
    color foreground = L_GRAY;
    color background = BLACK;
    if (fd == STDERR) {
        foreground = RED;
    }
    int i;
    for (i = 0; i < count; i++) {
        if(buf[i] == '\n'){
            ncNewline(fd);
        }
        else if(buf[i] == '\t'){
            ncPrint(fd, "    ");
        }
        else if(buf[i] == 8){
            if (fd == 1) {
                ncBackspace();
            }
        }
        else{
            ncPrintColorfulChar(fd, buf[i], foreground, background);
        }
    }
    return i;
}

int sys_read(unsigned int fd, char * buf, unsigned int count){
    int i;
    char * buffer = get_buffer();
    int dim = get_dim();
    for( i = 0 ; i < count && i < dim ; i++){
        buf[i] = buffer[i];
    }
    for(int j = 0, k = i, len_to_copy = dim - i ; j < len_to_copy ; j++, k++){
        buffer[j] = buffer[k];
    }
    update_dim(dim - i);
    return i;
}

int sys_clear(uint64_t rdi, uint64_t rsi, uint64_t rdx){
    ncClear();
    return 1;
}

int sys_seconds_elapsed(uint64_t rdi, uint64_t rsi, uint64_t rdx) {
    return seconds_elapsed();
}

int sys_datetime(uint64_t * info, uint64_t rsi, uint64_t rdx){
    for(int i = 0; i < 6; i++){
        uint64_t aux = realtime[i]();
        info[i] = aux;
    }
    return 1;
}

int sys_print_byte_from_mem(unsigned int fd, uint8_t * address, uint64_t rdx) {
    ncPrint(fd, "0x");
    ncPrintHex(fd, (uint64_t) address);
    ncPrint(fd, "=");
    
    int n = *address;
    int digits = 0;
    while (n > 0) {
        digits++;
        n /= 16;
    }

    if (digits <= 1) {
        ncPrint(fd, "0");
    }
    ncPrintHex(fd, *address);
    return 1;
}

int sys_start_split_screen(uint64_t rdi, uint64_t rsi, uint64_t rdx) {
    // if(functions != 0 && functions[0] != 0 && functions[1] != 0) {
    ncStartSplitScreen();
    //     int pid_left = es(functions[0],args_f1->integer,args_f1->string);
    //     int pid_right = load_processes(functions[1],args_f2->integer,args_f2->string);
    //     activate_scheduler();
    // }
    return 1;
}

// Load Process
int sys_load_process(uint64_t function, arguments * args_function, uint64_t rdx) {
    int pid = -1;
    if(function != 0 && args_function != 0) {
        pid = load_processes(function, args_function->integer, args_function->string);
    }
    return pid;
}

// Pause Process (para terminal y userland. se corre demas programas y quedan en
// estado de hibernacion)
int sys_hibernate_process(int pid, uint64_t rsi, uint64_t rdx) {
    return hibernate_process(pid);
}

