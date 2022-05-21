#include <syscalls.h>
#include <divide_by_zero.h>

extern void invalid_opcode();

static int var1 = 0;
static int var2 = 0;

int main() {

	write(1, "HOLA", 4);
	char hola[1];
	int ret = 0;
	while (1) {
		while(ret == 0){
			ret = read(1,hola,1);
		}
		write(1,hola,1);
		if (hola[0] == '1') {
			divide_by_zero();
		}
		if (hola[0] == '2') {
			invalid_opcode();
		}
		ret = 0;
	}

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}

void prueba() {
	return;
}