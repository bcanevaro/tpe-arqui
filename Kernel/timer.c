#include <timer.h>
#include <scheduler.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
	if (ticks % 6 == 0 && get_current_pid() == 2) {
		ncBlinkCursor();
	}
	scheduler();
}

// Me devuelve la cantidad de ticks que pasaron.
int ticks_elapsed() {
	return ticks;
}

// Me devuelve la cantidad de segundos que pasaron.
int seconds_elapsed() {
	return ticks/18;
}

int miliseconds_elapsed(){
	return (ticks*1000)/18;
}
