#include <timer.h>
#include <keyboard.h>
#include <stdint.h>

typedef void (*int_function)(void);
static void int_20();
static void int_21();
static int_function interruptions[] = {&int_20, &int_21};

// Arreglar para que quede como un arreglo de punteros a funcion
void irqDispatcher(uint64_t irq) {
	interruptions[irq]();
	return;
}

void int_20() {
	timer_handler();
}

void int_21() {
	keyboard_handler();
}
