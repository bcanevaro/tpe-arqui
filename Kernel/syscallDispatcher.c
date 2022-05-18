#include <stdint.h>
#include <naiveConsole.h>
#include <defs.h>

static int sys_write(unsigned int fd, const char * buf, unsigned int count);

// Arreglar para que quede como un arreglo de punteros a funcion
int syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t syscall_number) {
	int ret;
    switch (syscall_number) {
		case 0:
			
			break;
		case 1:
			ret = sys_write(rdi, rsi, rdx);
			break;
	}
	return ret;
}

static int sys_write(unsigned int fd, const char * buf, unsigned int count) {
    color foreground = L_GRAY;
    color background = BLACK;
    if (fd == STDERR) {
        foreground = RED;
    }
    int i;
    for (i = 0; i < count; i++) {
        ncPrintColorfulChar(buf[i], foreground, background);
    }
    return i;
}

