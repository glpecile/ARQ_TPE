/**
 * Dispachers para las system calls usadas en Userland.
*/
#include <keyboardDriver.h>
#include <rtcDriver.h>
#include <videoDriver.h>
#include <time.h>
#include <stdint.h>

// uint64_t sWrite(char *buffer, int size);
// uint64_t sRead(int fd, char *buffer, int lenght);

uint64_t systemDispatcher(uint64_t rdi, ...) {
    switch (rdi)
    {
        case 0:
            return sTicksElapsed();
            break;
        case 1:
            // return getTime(rsi);
            break;
        case 2:
            // return sRead(int fd, char *buffer, int lenght);
            break;
        case 3:
            // return sWrite(char *buffer, int size);
            break;
        case 4:
            return sGetChar();
            break;
        case 5:
            break; 
        
        default:
            break;
    }
}