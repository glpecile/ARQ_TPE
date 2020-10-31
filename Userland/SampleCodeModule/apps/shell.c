/**
 * shell.c: Intérprete de comandos de funciones de kernel.
*/
#include <shell.h>

#define MAX_INPUT 15
#define MAX_SIZE 10
#define MAX_ARGUMENTS 3

t_command commands[MAX_SIZE];
static int sizeC = 0;

void intializeShell()
{
    int exit = 0;
    char input[MAX_INPUT];
    //loadCommands();
    while (1)
    {
        readInput(input, MAX_INPUT);
        exit = !processInput(input);
        _setCursor(0, HEIGHT - 1);
    }
}

// void loadCommands(){
//     loadCommand(&infoReg, "infoReg","Prints all the registers.\n");
//     loadCommand(&help, "help","Prints the description of all functions.\n");
//     loadCommand(&printCurrentTime,"Date & Time","Prints the current time. Args: -h prints current hours.  -m prints current minutes.  -s prints current seconds.\n");
//     loadCommand(&printMem, "Printmem","Makes a 32 Bytes memory dump to screen from the address passed by argument.\nAddress in hexadecimal and 0 is not valid.\n" );
//     loadCommand(&chess,"chess", "Chess game, play a 1v1 match against a friend or yourself!\n");
//     loadCommand(&invalidOpCodeException, "invalidOpCodeException","Displays exception of an invalid operation code.\n");
//     loadCommand(&invalidZeroDivisionException, "invalidZeroDivisionException","Displays exception of an invalid division by zero.\n");
// }

void loadCommand(void (*fn)(), char *name, char *desc)
{
    commands[sizeC].command = fn;
    commands[sizeC].name = name;
    commands[sizeC].description = desc;
    sizeC++;
}

void readInput(char *inputBuffer, int maxSize)
{
    int size = 0;
    char c;
    while (size < maxSize && (c = getChar()) != '\n')
    {
        if (c != '\b')
        {
            inputBuffer[size++] = c;
            putChar(c);
        }
        else if (size > 0)
        {
            putChar('\b');
            size--;
        }
    }
    inputBuffer[size++] = 0;
    putChar('\n');
}

int processInput(char *inputBuffer)
{
    char *arguments[MAX_ARGUMENTS];
    int numArgs = strtok(inputBuffer, ' ', arguments, MAX_ARGUMENTS);
    for (int i = 0; i < sizeC; i++)
    {
        if (strcmp(arguments[0], commands[i].name))
        {
            commands[i].command(numArgs, arguments + 1);
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
    static char *regs[] = {
        "RAX: ", "RBX: ", "RCX: ", "RDX: ", "RBP: ", "RDI: ", "RSI: ",
        "R8: ", "R9: ", "R10: ", "R11: ", "R12: ", "R13: ", "R14: ", "R15: "};
}
