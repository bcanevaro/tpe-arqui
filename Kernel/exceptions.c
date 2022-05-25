#include <naiveConsole.h>
#include <syscallDispatcher.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6


static void zero_division();
static void invalid_opcode();
typedef void (*Exception)(void);
static void excepHandler(char * msg);
extern void continue_execution();
extern void _hlt();


static Exception exceptions[]={&zero_division, 0, 0, 0, 0, 0, &invalid_opcode};
static char * message[] = {"Zero Division Exception", "Invalid Opcode Exception"};

void exceptionDispatcher(int exception) {
  Exception ex = exceptions[exception];
	if(ex != 0){
		ex();
	}
}

//CAMBIAR ESTO
static void excepHandler(char * msg){
	ncPrintColorful(1 ,msg, RED, WHITE);
	ncColorfulNewline(1, WHITE);
	ncPrintColorful(1, "Presione enter para continuar", RED, WHITE);
	char c[1];
	do{
		_hlt();		// halts the central processing unit until the next external interrupt is fired.
	} while(sys_read(1, c, 1) != 1 || c[0] != '\n');
	ncClear();
	continue_execution();
}

static void zero_division() {
	excepHandler(message[0]);
}

static void invalid_opcode(){
	excepHandler(message[1]);
}