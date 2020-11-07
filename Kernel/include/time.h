#ifndef _TIME_H_
#define _TIME_H_

void timerHandler();
int sTicksElapsed();
int secondsElapsed();
void timerFunc(void(*f), int toDo);

#endif
