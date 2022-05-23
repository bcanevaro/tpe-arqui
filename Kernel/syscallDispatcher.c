#include <timer.h>
#include <stdint.h>
#include <naiveConsole.h>
#include <defs.h>
#include <keyboard.h>
#include <syscallDispatcher.h>
#include <functions.h>

typedef int (*sys_call)(unsigned int, char *, unsigned int);
static sys_call system_call[] = {&sys_read, &sys_write, &sys_clear, &sys_seconds_elapsed, &sys_datetime};

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
            ncNewline();
        }
        else if(buf[i] == '\t'){
            ncPrint("    ");
        }
        else if(buf[i] == 8){
            ncBackspace();
        }
        else{
            ncPrintColorfulChar(buf[i], foreground, background);
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

int sys_datetime(uint64_t * rdi, uint64_t rsi, uint64_t rdx){
    for(int i = 0; i < 6; i++){
        uint64_t aux = realtime[i]();
        rdi[i] = aux;
    }
    return 1;
}