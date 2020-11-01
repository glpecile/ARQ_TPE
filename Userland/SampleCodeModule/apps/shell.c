/**
 * shell.c: Intérprete de comandos de funciones de kernel.
*/
#include <shell.h>

#define MAX_INPUT 10
#define MAX_SIZE 10
#define MAX_ARGUMENTS 3
#define REG_SIZE 15

t_command commands[MAX_SIZE];
static int sizeC = 0;

void intializeShell()
{
    int exit = 0;
    char input[MAX_INPUT];
    //loadCommands();
    _setCursor(0, HEIGHT-CHAR_HEIGHT);
    while (1) // !exit
    {
        readInput(input, MAX_INPUT);
        exit = processInput(input);
    }
}

//void loadCommands(){
//     loadCommand(&infoReg, "infoReg","Prints all the registers.\n");
//     loadCommand(&help, "help","Prints the description of all functions.\n");
//     loadCommand(&printCurrentTime,"Date & Time","Prints the current time. Args: -h prints current hours.  -m prints current minutes.  -s prints current seconds.\n");
//     loadCommand(&printMem, "Printmem","Makes a 32 Bytes memory dump to screen from the address passed by argument.\nAddress in hexadecimal and 0 is not valid.\n" );
//     loadCommand(&chess,"chess", "Chess game, play a 1v1 match against a friend or yourself!\n");
//     loadCommand(&invalidOpCodeException, "invalidOpCodeException","Displays exception of an invalid operation code.\n");
//     loadCommand(&invalidZeroDivisionException, "invalidZeroDivisionException","Displays exception of an invalid division by zero.\n");
//}

void loadCommand(void (*fn)(), char *name, char *desc)
{
    commands[sizeC].command = fn;
    commands[sizeC].name = name;
    commands[sizeC].description = desc;
    sizeC++;
}

void readInput(char *inputBuffer, int maxSize)
{
    // print("Entre.");
    int size = 0;
    uint64_t c;
    while (size < (maxSize - 1) && (c = getChar()) != '\n'){
        // putChar(c);
        if (c != '\b')
        {
            putChar(c);
            inputBuffer[size++] = c;

        }
        else if (size > 0)
        {
            putChar('\b');
            size--;
        }
    }
    inputBuffer[size++] = 0;
    putChar('d');
    putChar('\n');
}

int processInput(char *inputBuffer)
{
    char *args[MAX_ARGUMENTS];
    int argSize = strtok(inputBuffer, ' ', args, MAX_ARGUMENTS);
    // if(argSize < 1){
    //     print("invalid argument");
    //     return 0;
    // }
    for (int i = 0; i < sizeC; i++)
    {
        if (strcmp(args[0], commands[i].name))
        {
            commands[i].command(argSize, args + 1);
            return 1;
        }
    }
    return 0;
}

/****************** COMANDOS ******************/
void help()
{
    for (int i = 0; i < sizeC; i++)
    {
        print(commands[i].name);
        print(":");
        print(commands[i].description);
        putChar('\n');
    }
}

void inforeg(uint64_t *reg)
{
    static char *regs[REG_SIZE] = {
        "RAX: ", "RBX: ", "RCX: ", "RDX: ", "RBP: ", "RDI: ", "RSI: ",
        "R8: ", "R9: ", "R10: ", "R11: ", "R12: ", "R13: ", "R14: ", "R15: "};

    //_sRegs(regs); HACER ESTO
    char buffer[20];
    for (int i = 0; i < REG_SIZE; i++)
    {
        print(regs[i]);
        print(":  0x");
 //       uintToBase(regs[i],buffer,16);
        putChar('\n');
    }
}

void printCurrentTime()
{
}

// void printMem(){
// uint64_t num;
//    char buffer[32]; 
// uint8_t * address = (uint8_t *) num;

    // for (int i = 0; i < 4; i++){
    //     for (int j = 0; j < 8; j++){
    //         uintToBase(*(address + 8*i + j), buffer, 16);
    //         print(buffer);
    //         putchar(' ');
    //     }
    //     putchar('\n'); 
    // } 
// }