/**
 * chessConsole.c: Driver consola 
*/
#include <chessConsole.h>
typedef struct
{
    int x;
    int y;
} t_currentPos;
static t_currentPos currentPos;
/**
 * LIFO para los log de los movimientos. 
 * Nunca se popean porque es necesario que 
 * queden guardados los log para usarlos mas tarde.
 */
static char *log[LAST_LINE];
static int currentSize = 0;
/**
 *  Imprime en una posicion y color determinado de la pantalla,
 * luego retorna a su posicion original.
 */ 
void printIn(char *string, int x, int y, int color)
{
    int aux_x = currentPos.x; 
    _setCursor(x, y);
    printWithColor(string, color);
    _setCursor(aux_x, LAST_LINE);
}
void initializeCursor()
{
    _setCursor(0, LAST_LINE);
    currentPos.x = 10;
    currentPos.y = LAST_LINE;
}

// idea: divide output de error en dos. Descartada.
// void printCommand(char *string)
// {
//     int length = strlen(string);
//     int diff = length - THRESHOLD;
//     char toPrint[2];
//     numToStr(diff, toPrint, 2);
//     print(toPrint);
//     if (diff <= 0)
//     {
//         printIn(string, PLAYER_LENGTH, LAST_LINE, WHITE);
//     }
//     else
//     {
//         char str1[length - diff + 1];
//         char str2[diff + 1];
//         memcpy(str1, string, THRESHOLD);
//         memcpy(str2, string + THRESHOLD, diff);
//         str1[diff] = '\0';
//         str2[length - diff] = '\0';
//         print(str1);
//         currentPos.y += CHAR_HEIGHT;
//         printIn(str2, 0, currentPos.y, WHITE);
//     }
// }

// Imprime una linea nueva de comando en el log
void printLogLine(char *move, int player)
{
    clearLine(LAST_LINE);
    addMoveToLog(move, player);
    int i = 0;
    char *toPrint;
    while (i < currentSize)
    {
        // print("se entro al while...");
        toPrint = getNextMove(i);                     // Consigue el movimiento a imprimir.
        printPlayer(((i + 2) % 2) + player, LAST_LINE - i-1); // Imprime al jugador del movimiento.
        printIn(toPrint, 10, LAST_LINE - i -1, WHITE);         // Imprime el movimiento.
        i++;
    }
    
}
void printPlayer(int number, int line)
{
    char *aux;
    switch (number)
    {
    case PLAYER1:
        aux = "Player 1: ";
        break;
    case PLAYER2:
        aux = "Player 2: ";
        break;
    default:
        break;
    }
    //currentPos.x+=10;
    printIn(aux, 0, line, GREEN);
}
void clearLine(int y)
{
    // for (int i = 0; i < MAX_WIDTH / CHAR_WIDTH; i++)
    // {
    //     _drawRectangle(getHorizontalPixelPosition(i), getVerticalPixelPosition(y), CHAR_WIDTH, CHAR_HEIGHT, BLACK);
    // }
    char toDraw[] = "X";
    for (int i = 0; i < MAX_WIDTH / CHAR_WIDTH - CHAR_WIDTH; i++)
    {
        _drawFigure(toDraw, BLACK, CHAR_HEIGHT, getHorizontalPixelPosition(i), getVerticalPixelPosition(y));
    }
}
int getVerticalPixelPosition(int value)
{
    return CHAR_HEIGHT * value;
}
int getHorizontalPixelPosition(int value)
{
    return CHAR_WIDTH * value;
}
// Se agrega un nuevo movimiento al log.
void addMoveToLog(char *move, int player)
{
    // print("Se agrego...");
    // if (currentSize != 0 && currentSize % LAST_LINE == 0)
    // {
    //     moveUpLog();
    //     // print("se hace el moveUpLog()...");
    // }
    log[currentSize++] = move; // Guardamos el movimiento.
}
// Se mueven todos los log una posicion para "arriba" eliminando al primer log ingresado.
// Esto se hace para el estilo de scroll up.
void moveUpLog()
{
    for (int i = 1; i < HEIGHT; i++)
    {
        log[i - 1] = log[i];
    }
    currentSize--;
}
char *getNextMove(int i)
{
    // print("getting move...");
    return log[currentSize - 1 - i];
}
void updateTimerConsole(int time)
{
    char aux[30];
    uintToBase(time, aux, 10);
    printIn(aux, (MAX_WIDTH/CHAR_WIDTH) + 5, LAST_LINE, RED);
}

void displayChar(char c) {
    putChar(c);
    if (c == '\b') {
        currentPos.x-=1;
    }else{
        currentPos.x+=1;
    }    
}

void printEntireLog(){
    char aux[30];
    uintToBase(currentSize, aux, 10);
    printIn(aux, 2, 2, RED);
    for(int i = 0; i<currentSize; i++){
        printIn(log[i],0,i,RED);
    }
}
void resetCursor(){
    _setCursor(10, LAST_LINE);
    currentPos.x = 10;
    currentPos.y = LAST_LINE;
}