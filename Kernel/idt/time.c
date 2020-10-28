#include <time.h>

static unsigned long ticks = 0;

void timerHandler() {
	ticks++;
}

int sTicksElapsed() {
	return ticks;
}

int secondsElapsed() {
	return ticks / 18;
}
