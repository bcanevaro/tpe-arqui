#include <syscalls.h>
#include <divide_by_zero.h>
#include <terminal.h>

static int var1 = 0;
static int var2 = 0;

void infinite_terminal(){
	do{
		terminal();
	}while(1);
}

int main() {
	clear_screen();
	arguments terminal_arguments = {-1,-1};
	load_process(&infinite_terminal, &terminal_arguments);
	hibernate_process(1);

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}