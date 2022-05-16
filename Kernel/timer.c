#include <timer.h>

static unsigned long ticks = 0;

// Maneja el RTC.
void timer_handler() {
	ticks++;
}

// Me devuelve la cantidad de ticks que pasaron.
int ticks_elapsed() {
	return ticks;
}

// Me devuelve la cantidad de segundos que pasaron.
int seconds_elapsed() {
	return ticks / 18;
}