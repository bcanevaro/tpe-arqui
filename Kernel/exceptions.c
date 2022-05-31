#include <naiveConsole.h>
#include <syscallDispatcher.h>
#include <scheduler.h>

#define ALL_REGISTER_COUNT 20
static char * register_names[] = {"   RAX=", "   RBX=", "   RCX=", "   RDX=", "   RBP=", "   RDI=", "   RSI=", "    R8=",
                                  "    R9=", "   R10=", "   R11=", "   R12=", "   R13=", "   R14=", "   R15=", "   RIP=",
								  "    CS=", "RFLAGS=", "   RSP=", "    SS="};


static void zero_division(uint64_t * registers);
static void invalid_opcode(uint64_t * registers);
typedef void (*Exception)(uint64_t *);
static void excepHandler(int message_index, uint64_t * registers);


static Exception exceptions[]={&zero_division, 0, 0, 0, 0, 0, &invalid_opcode};
static char * message[][2] = {{"----- Zero Division Exception --------------------------------------------------", "----- Invalid Opcode Exception -------------------------------------------------"},
							  {"----- Zero Division Exception ---------", "----- Invalid Opcode Exception --------"}};
static char * separator[2] = {"--------------------------------------------------------------------------------",
							  "---------------------------------------"};

void exceptionDispatcher(int exception, uint64_t * registers) {
	Exception ex = exceptions[exception];
	if(ex != 0){
		ex(registers);
	}
}

/*
						PID		FD
Pantalla Central		3		2
Pantalla Izquierda		3		4
Pantalla Derecha		4		6
*/
static void excepHandler(int message_index, uint64_t * registers) {
	int pid = get_current_pid();
	int fd = pid - 1;
	char in_split_screen = get_in_split_screen();
	if (in_split_screen) {
		fd *= 2;
	}
	ncNewline(fd);
	ncPrint(fd, message[in_split_screen][message_index]);
	ncNewline(fd);
	char buffer[17];
    for (int i = 0; i < ALL_REGISTER_COUNT; i++) {
        ncPrint(fd, register_names[i]);
		printRegisterFormat(fd, registers[i]);
		ncPrint(fd, " ");
		if ((i+1) % 3 == 0) {
			ncNewline(fd);
		}
    }
	ncNewline(fd);
	ncPrint(fd, separator[in_split_screen]);
	if (in_split_screen) {
		kill_split_process(pid);
	} else {
		kill_unique_process();
	}
}

static void zero_division(uint64_t * registers) {
	excepHandler(0, registers);
}

static void invalid_opcode(uint64_t * registers){
	excepHandler(1, registers);
}