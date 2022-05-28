#include <timer.h>
#include <scheduler.h>

static unsigned long ticks = 0;
static char first_scheduler_call = 1;

void prueba(){}

void timer_handler() {
	ticks++;
	if(is_scheduler_active()) {
		prueba();
		if(first_scheduler_call) {
			first_scheduler_call = 0;
			exec_process(0);
		}
		scheduler();
	}
}

// Me devuelve la cantidad de ticks que pasaron.
int ticks_elapsed() {
	return ticks;
}

// Me devuelve la cantidad de segundos que pasaron.
int seconds_elapsed() {
	return ticks / 18;
}