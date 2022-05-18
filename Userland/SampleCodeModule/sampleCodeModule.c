/* sampleCodeModule.c */

#include <syscalls.h>

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {

	write(1, "HOLA", 4);
	char hola [1];
	int ret = 0;
	while (1) {
		while(ret == 0){
			ret = read(1,hola,1);
		}
		write(1,hola,1);
		ret = 0;
	}

	//All the following code may be removed 
	*v = 'X';
	*(v+1) = 0x74;

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}

void prueba() {
	return;
}