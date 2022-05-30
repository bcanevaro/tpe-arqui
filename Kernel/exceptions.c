#include <naiveConsole.h>
#include <syscallDispatcher.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6

#define ALL_REGISTER_COUNT 20
static char * register_names[] = {"   RAX=", "   RBX=", "   RCX=", "   RDX=", "   RBP=", "   RDI=", "   RSI=", "    R8=",
                                  "    R9=", "   R10=", "   R11=", "   R12=", "   R13=", "   R14=", "   R15=", "   RIP=",
								  "    CS=", "RFLAGS=", "   RSP=", "    SS="};


static void zero_division(uint64_t * registers);
static void invalid_opcode(uint64_t * registers);
typedef void (*Exception)(uint64_t *);
static void excepHandler(char * msg, uint64_t * registers);
extern void continue_execution();
extern void _hlt();


static Exception exceptions[]={&zero_division, 0, 0, 0, 0, 0, &invalid_opcode};
static char * message[] = {"----- Zero Division Exception --------------------------------------------------", "----- Invalid Opcode Exception -------------------------------------------------"};
static char * separator = "--------------------------------------------------------------------------------";

void exceptionDispatcher(int exception, uint64_t * registers) {
  Exception ex = exceptions[exception];
	if(ex != 0){
		ex(registers);
	}
}

// FALTA QUE IMPRIMA LA EXCEPCION DE CADA LADO
static void excepHandler(char * msg, uint64_t * registers){
	ncPrint(2, msg);
	ncNewline(2);
	char buffer[17];
    for (int i = 0; i < ALL_REGISTER_COUNT; i++) {
        ncPrint(2, register_names[i]);
		printRegisterFormat(2, registers[i]);
		ncPrint(2, " ");
		if ((i+1) % 3 == 0) {
			ncNewline(2);
		}
    }
	ncNewline(2);
	ncPrint(2, separator);
	// ncClear();
	// continue_execution();
}

static void zero_division(uint64_t * registers) {
	excepHandler(message[0], registers);
}

static void invalid_opcode(uint64_t * registers){
	excepHandler(message[1], registers);
}