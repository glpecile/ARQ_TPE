#include <shell.h>

#define MAX_INPUT 15
void intializeShell(){
    
    char input[MAX_INPUT];  
    loadCommands();
    while(1){
        readInput(input, MAX_INPUT);
        processInput(input);
        setCursor(0,HEIGHT-1 );      
    }
}

void loadCommands(){
    loadCommand(&getRegs, "inforeg","Prints all the registers \n");
    loadCommand(&printArgs, "printArgs","Prints all its arguments\n ");
    loadCommand(&help, "help","Prints the description of all functions \n");
    loadCommand(&printCurrentTime, "clock","Prints the current time. Args: -h prints current hours.  -m prints current minutes.  -s prints current seconds.\n");
    loadCommand(&printmem, "printmem","Makes a 32 Bytes memory dump to screen from the address passed by argument.\nAddress in hexadecimal and 0 is not valid.\n" );
    loadCommand( &chess,"chess", "Chess game");
}

void loadCommand(void (*fn)(), char *name, char *desc){
    command[sizeC].
}
 