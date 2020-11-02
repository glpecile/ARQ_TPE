/**
 * shell.c: Intérprete de comandos de funciones de kernel.
*/
#include <shell.h>

#define MAX_INPUT 30
#define MAX_SIZE 10
#define MAX_ARGUMENTS 3
#define REG_SIZE 17

t_command commands[MAX_SIZE];
static int sizeC = 0;

void intializeShell()
{
    //int exit = 0;
    char input[MAX_INPUT];
    loadCommands();
    _setCursor(0, HEIGHT - CHAR_HEIGHT / 2);
    while (1) // !exit
    {
        printUser();
        readInput(input, MAX_INPUT);    
        processInput(input);
    }
}

void loadCommands()
{
    loadCommand(&inforeg, "inforeg", "Displays all the information regarding the registers.\n");
    loadCommand(&help, "help", "Displays the description of all functions available.\n");
    loadCommand(&printCurrentTime, "time", "Displays the current time and date.\n");
    loadCommand(&printmem, "printmem", "Makes a 32 Bytes memory dump to screen from the address passed by argument.\n");
    loadCommand(&invalidOpCodeException, "invalidOpCodeException", "Displays exception of an invalid operation code.\n");
    loadCommand(&invalidZeroDivisionException, "invalidZeroDivisionException", "Displays exception of an invalid division by zero.\n");
    loadCommand(&chess,"chess", "Chess game, play a 1v1 match against a friend or yourself!. Type -c to continue the previous match.\n");
}

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
    uint64_t c;
    while (size < (maxSize - 1) && (c = getChar()) != '\n')
    {
        if (c) // Verificamos que se presiona una letra.
        {
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
    }
    // Ponemos la marca de final al string.
    inputBuffer[size++] = 0;
    putChar('\n');
}

int processInput(char *inputBuffer)
{
    char *args[MAX_ARGUMENTS];
    int argSize = strtok(inputBuffer, ' ', args, MAX_ARGUMENTS);
    //verificamos la cant de args antes de compararlo con los existentes
    if (argSize <= 0 || argSize > 1)
    {
        print("Invalid amount of arguments, try again.\n");
        return 0;
    }
    for (int i = 0; i < sizeC; i++)
    {
        if (strcmp(args[0], commands[i].name))
        {
            commands[i].command(argSize - 1, args + 1);
            if(strcmp("time", commands[i].name))
                print("segui");
            return 1;           
        }
    }
    print("Invalid command, try again.\n");
    return 0;
}

/*
 ************************************ 
 * COMANDOS 
 ************************************
*/
void printUser(){
	char s[] = "Clifford@TPE_ARQ:$ ";
    printWithColor(s, LIGHT_BLUE);
}

void help()
{
    for (int i = 0; i < sizeC; i++)
    {
        printWithColor(commands[i].name, YELLOW);
        print(": ");
        print(commands[i].description);
        putChar('\n');
    }
}

void inforeg(uint64_t *reg)
{
    static char *regs[REG_SIZE] = {
        "RAX", "RBX", "RCX", "RDX", "RBP", "RDI", "RSI",
        "R08", "R09", "R10", "R11", "R12", "R13", "R14",
        "R15", "IP ", "RSP"};

    char toPrint[20];
    for (int i = 0; i < REG_SIZE; i++)
    {
        printWithColor(regs[i],YELLOW);
        uintToBase(reg[i], toPrint, 16);
        print(":");
        print(toPrint);
        putChar('\n');
    }
}
// void numToStr(int num, char *string, int len)
void printCurrentTime()
{
    char toPrint[2];
    char year[4];

    numToStr(_getTime(HOURS), toPrint, 2);
    print(toPrint);
    print(":");
    numToStr(_getTime(MINUTES), toPrint, 2);
    print(toPrint);
    print(", ");
    numToStr(_getTime(DAY_OF_THE_MONTH), toPrint, 2);
    print(toPrint);
    print("/");
    numToStr(_getTime(MONTH), toPrint, 2);
    print(toPrint);
    print("/");  
    numToStr(_getTime(YEAR) + 2000, year, 4);
    print(year);
    putChar('\n');
}

void printmem(int argSize, char *args[])
{
    uint64_t num = hexaToInt(args[0]);
    char toPrint[32];

    for (int i = 0; i < 32; i++)
    {
        uintToBase((num + i), toPrint, 16);
        printHex(toPrint[i]);
        putChar(' ');
    }
    putChar('\n');
}

// source: https://www.felixcloutier.com/x86/ud.
void invalidOpCodeException()
{
    __asm__("ud2");
}

void invalidZeroDivisionException()
{
    int a = 0, b = (1 / a); // dividimos por 0.
    if (b)
    {
    }
}

void chess(int argSize, char *args[]){
    if(argSize == 0)
        startGame(NEW_GAME);
    if(strcmp(args[0], "-c"))
        startGame(CONTINUE_GAME);
}