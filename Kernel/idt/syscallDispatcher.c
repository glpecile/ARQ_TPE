/**
 * Dispachers para las system calls usadas en Userland.
 * Preservamos syscalls similares o inspiradas en las existentes de Linux.
*/
#include <keyboardDriver.h>
#include <rtcDriver.h>
#include <videoDriver.h>
#include <time.h>
#include <stdint.h>

// uint64_t sWrite(char *buffer, int size);
// uint64_t sRead(int fd, char *buffer, int lenght);

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx)
{
    switch (rdi)
    {
        case 0:
            return sTicksElapsed();
        case 1:
            return getTime(rsi);
        case 2:
            // return sRead(int fd, char *buffer, int lenght);
            break;
        case 3:
            // return sWrite(char *buffer, int size);
            break;
        case 4:
            return sGetChar();          
        case 5:
            break; 
        
        default:
            break;
    }
    return 0;
}