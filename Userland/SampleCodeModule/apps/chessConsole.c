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

static char log[LAST_LINE][7];
static int playerOrder[LAST_LINE];
int currentSize = 0;
/**
 *  Imprime en una posicion y color determinado de la pantalla,
 * luego retorna a su posicion original.
 */ 
void printIn(char *string, int x, int y, int color)
{
    int aux_x = currentPos.x; 
    _setCursor(x, y,BLACK);
    printWithColor(string, color);
    _setCursor(aux_x, LAST_LINE,BLACK);
}
void initializeCursor()
{
    _setCursor(0, LAST_LINE,BLACK);
    currentPos.x = 10;
    currentPos.y = LAST_LINE;
}
void initializeLog(){
    currentSize = 0;
}
// Imprime una linea nueva de comando en el log
void printLogLine(char *move, int player)
{
    clearLine(LAST_LINE);
    addMoveToLog(move, player);
    printEntireLog();
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
    printIn(aux, 0, line, GREEN);
}
void clearLine(int y)
{
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
    memcpy(log[currentSize], move, 6);
    playerOrder[currentSize++] = player;
}

// Se mueven todos los log una posicion para "arriba" eliminando al primer log ingresado.
// Esto se hace para el estilo de scroll up.
void updateTimerConsole(int time)
{
    char aux[30];
    uintToBase(time, aux, 10);
    printIn(aux, (MAX_WIDTH/CHAR_WIDTH) + 5, LAST_LINE, YELLOW);
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
    for(int i = 0; i<currentSize; i++){
        char aux1[2];
        uintToBase(playerOrder[currentSize - 1 - i], aux1, 10);
        printIn(aux1, 0, LAST_LINE - i -1 , GREEN);
        printIn(log[currentSize-1-i], 5, LAST_LINE - i -1, WHITE);         // Imprime el movimiento.
    }
    resetCursor();
}
void resetCursor(){
    _setCursor(10, LAST_LINE,BLACK);
    currentPos.x = 10;
    currentPos.y = LAST_LINE;
}