#include <stdint.h>
#include <naiveConsole.h>
#include <defs.h>
#include <keyboard.h>

static int sys_write(unsigned int fd, const char * buf, unsigned int count);
static int sys_read(unsigned int fd, char * buf, unsigned int count);



// Arreglar para que quede como un arreglo de punteros a funcion
int syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t syscall_number) {
	int ret;
    switch (syscall_number) {
		case 0:
			ret = sys_read(rdi,rsi,rdx);
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
            ncPrintChar(buf[i]);
        }
    }
    return i;
}

static int sys_read(unsigned int fd, char * buf, unsigned int count){
    int i,j,k;
    char * buffer = get_buffer();
    int dim = get_dim();
    for( i = 0 ; i < count && i < dim ; i++){
        buf[i] = buffer[i];
    }
    for(j = 0 , k = i ; j <= dim - i ; j++, k++,dim--){
        buffer[j] = buffer[k];
    }
    update_dim(dim);
    return i;
}