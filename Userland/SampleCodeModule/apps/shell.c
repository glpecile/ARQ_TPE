/**
 * shell.c: Intérprete de comandos de funciones de kernel.
*/
#include <shell.h>

#define MAX_INPUT 30
#define MAX_SIZE 10
#define MAX_ARGUMENTS 3
#define REG_SIZE 17
#define ESC 27

t_command commands[MAX_SIZE];
static int sizeC = 0;

void intializeShell()
{
    char input[MAX_INPUT];
    loadCommands();
    _setCursor(0, HEIGHT - 1, GREEN);
    while (1) // !exit
    {
        printUser();
        readInput(input, MAX_INPUT, ESC);
        putChar('\n');
        processInput(input);
    }
}

void loadCommands()
{
    loadCommand(&help, "help", "Displays the description of all functions available.\n");
    loadCommand(&getRegs, "inforeg", "Displays all the information regarding the registers.\n");
    loadCommand(&printmem, "printmem", "Makes a 32 Bytes memory dump to screen from the address passed by argument.\n");
    loadCommand(&printCurrentTime, "time", "Displays the current time and date.\n");
    loadCommand(&invalidOpCodeException, "invalidOpCodeException", "Displays exception of an invalid operation code.\n");
    loadCommand(&invalidZeroDivisionException, "invalidZeroDivisionException", "Displays exception of an invalid division by zero.\n");
    loadCommand(&chess, "chess", "Play a 1v1 match against a friend or yourself!.\nType 'chess -c' to continue the previous match.\nType 'chess -man' to display instructions.\n");
    loadCommand(&_clearScreen, "clear", "Clears the whole screen.\n");
}

void loadCommand(void (*fn)(), char *name, char *desc)
{
    commands[sizeC].command = fn;
    commands[sizeC].name = name;
    commands[sizeC].description = desc;
    sizeC++;
}

int readInput(char *inputBuffer, int maxSize, char token)
{
    int size = 0;
    uint64_t c;
    while (size < (maxSize - 1) && (c = getChar()) != '\n' && c != token)
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
    return c != token;
}

int processInput(char *inputBuffer)
{
    char *args[MAX_ARGUMENTS];
    int argSize = strtok(inputBuffer, ' ', args, MAX_ARGUMENTS);
    // Verificamos la cant de args antes de compararlo con los existentes.
    if (argSize <= 0 || argSize > 2)
    {
        print("Invalid amount of arguments, try again.\n");
        return 0;
    }
    for (int i = 0; i < sizeC; i++)
    {
        if (strcmp(args[0], commands[i].name))
        {
            commands[i].command(argSize - 1, args + 1);
            return 1;
        }
    }
    print("Invalid command, try again.\n");
    return 0;
}

int getScreenHeight()
{
    return _getPixelHeight() / CHAR_HEIGHT;
}

int getScreenWidth()
{
    return _getPixelWidth() / CHAR_WIDTH;
}

/*
 ************************************ 
 * COMANDOS 
 ************************************
*/
void printUser()
{
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

    char toPrint[30];
    for (int i = 0; i < REG_SIZE; i++)
    {
        printWithColor(regs[i], YELLOW);
        uintToBase(reg[i], toPrint, 16);
        print(":");
        print(toPrint);
        putChar('\n');
    }
}

void printCurrentTime()
{
    printInt(_getTime(HOURS));
    print(":");
    printInt(_getTime(MINUTES));
    print(", ");
    printInt(_getTime(DAY_OF_THE_MONTH));
    print("/");
    printInt(_getTime(MONTH));
    print("/");
    printInt(_getTime(YEAR) + 2000);
    putChar('\n');
}

void printmem(int argSize, char *args[])
{
    uint64_t num = hexaToInt(args[0]);
    if (argSize < 1 || num == 0)
    {
        print("Invalid argument. Try again.\n");
        return;
    }
    char toPrint[32];
    uint8_t *mem_address = (uint8_t *)num;
    for (int i = 0; i < 32; i++)
    {
        uintToBase(mem_address[i], toPrint, 16);
        print(toPrint);
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

void chess(int argSize, char *args[])
{
    _clearScreen();
    if (argSize == 0)
        startGame(NEW_GAME);
    if (strcmp(args[0], "-c"))
        startGame(CONTINUE_GAME);
    if (strcmp(args[0], "-man"))
    {
        printWithColor("CHESS MANUAL.\n", BEIGE);
        // Separado en más llamados a print ya que al usar un string muy largo genera errores.
        print("- Valid moves: 'FROM_X''FROM_Y' 'TO_X''TO_Y', caps lock should be enabled and the move should be valid to end your turn.\n");
        print("- Castling: short 'e 2' or 'e 3'.\n");
        print("- Coronation: By default a pawn transforms into a queen.\n");
        print("- Rotate: 'r' to rotate 90 degrees the board.\n");
        print("- Exit: 'ESC' to leave the game.\n");
    }
}
