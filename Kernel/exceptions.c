#include <naiveConsole.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6


static void zero_division();
static void invalid_opcode();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
	}else if ( exception == INVALID_OPCODE_EXCEPTION_ID){
		invalid_opcode();
	}	
}
// Handler para manejar la excepcion de division por cero
static void zero_division() {
	// Printear los registros y tambien el RIP
	ncNewline();
	ncPrintColorful("Zero Division Exception", RED, BLACK);
	ncNewline();
}
// Handler para manejar la excepcion de invalid opcode
static void invalid_opcode() {
	// Printear los registros y tambien el RIP
	ncNewline();
	ncPrintColorful("Invalid Opcode Exception", RED, BLACK);
	ncNewline();
}