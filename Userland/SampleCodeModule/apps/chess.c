/**
 * chess.c: Juego de ajedrez.
*/
#include <chess.h>
#define MAX_INPUT 8
#define MAX_ARGUMENTS 4
#define ESC 27
#define FALSE 0
#define TRUE 1
#define FIRST_ROW 0
#define FINAL_ROW 7
#define abs(x) (x < 0) ? -x : x

t_tile board[8][8];
char input[MAX_INPUT];
char *piecesCoronation[4] = {"QUEEN", "ROOK", "BISHOP", "KNIGHT"};
static typePieces toCoronation = 4;
static int jaqueP1 = 0, jaqueP2 = 0;

int timer_player1 = 0, timer_player2 = 0, currentPlayer = PLAYER1, skip_turn = FALSE, rotation = 4;

static t_piece initializePiece(int posX, int posY, typePieces name, int color, int player);
static void initializeBoard();
static void drawPieces(int x, int y);
static int fetchMovement(t_piece piece, int toX, int toY);

static void deleteFigure(t_piece toPiece);
static t_tile getTile(int x, int y);
static void move(t_piece piece, int toX, int toY);

static void findKing(int player, int *posXK, int *posYK, int *col);
static int prevJaque(t_piece fromPiece, int *posXK, int *posYK, int *col);
static int isEmptyP(int fromX, int fromY, int toX, int toY);
static int isEmptyN(int fromX, int fromY, int toX, int toY);
int checkPeonAlPaso(t_piece piece, int toX, int toY);
void rotate();
void drawFigure();
void printCoord();

void game();
int readPlayerInput(char *inputBuffer, int maxSize, char token);
void startTimer(int player);
void endTimer();
void activeTimer();
void pauseTimer();
void resumeTimer();

void startGame(int mode)
{
    _clearScreen();
    drawBoard(MAX_WIDTH, 0);
    printCoord();

    if (mode == NEW_GAME)
    {
        rotation = 4;
        initializeCursor();
        initializeBoard();
        initializeLog();
        drawPieces(MAX_WIDTH, 0);
        currentPlayer = PLAYER1;
        startTimer(currentPlayer);
    }
    else if (mode == CONTINUE_GAME)
    {
        printEntireLog();
        drawPieces(MAX_WIDTH, 0);
        resumeTimer();
    }
    // Cambiar.
    printPlayer(currentPlayer, LAST_LINE);
    game();
    _setCursor(0, LAST_LINE, GREEN);
}

void game()
{
    int quit = 0;
    while (quit == 0)
    {
        skip_turn = FALSE;
        quit = readPlayerInput(input, MAX_INPUT, ESC);
    }
    _clearScreen();
    if (quit == -1)
    {
        (currentPlayer == PLAYER1) ? print("Game Over. Player 2 has won!") : print("Game Over. Player 1 has won!");
        putChar('\n');
        endTimer();
    }
    if (quit == 3)
    {
        // Se mato al rey enemigo.
        (currentPlayer == PLAYER2) ? print("Game Over. Player 2 has won!") : print("Game Over. Player 1 has won!");
        putChar('\n');
        endTimer();
    }
    if (quit == 1)
    {
        pauseTimer();
    }
}

int processGame(char *inputBuffer)
{
    char *args[MAX_ARGUMENTS];
    int argSize = strtok(inputBuffer, ' ', args, MAX_ARGUMENTS);
    // Solo se permiten hasta 2 arg, el origen y el destino
    if (argSize <= 0 || argSize > 2)
        return 0;

    int position[4] = {-1, -1, -1, -1};
    int dimPosition = 0;

    for (int i = 0; i < argSize; i++)
    {
        //A1 A2
        int letter = args[i][0];
        int num = args[i][1];
        int flag = letter >= 'A' && letter <= 'H' && num >= '1' && num <= '8';
        if (!flag)
        {
            if (letter == 'e' && (num == '2' || num == '3'))
            { //verificamos si entro un e y long, para hacer enroque
                num = num - '0' - 1;
                enroque(num);
                return 1;
            }
            for (int j = 0; j < 4; j++)
            {
                if (strcmp(args[0], piecesCoronation[j]))
                {
                    toCoronation = j; //paso el tipo de pieza
                    return 1;
                }
            }
            return 0; //"Invalid input, please use the correct notation."
        }
        position[dimPosition++] = letter - 'A';
        position[dimPosition++] = num - '0' - 1;
    }

    return validMovePieces(position);
}

int validMovePieces(int position[4])
{
    int fromX = position[0]; // A - H COLUMNA
    int fromY = position[1]; // 0 - 7 FILA
    int toX = position[2];   //A-H COLUMNA
    int toY = position[3];   //0 -7 FILA
    // X son columnas e Y son las filas.
    t_tile space = board[fromX][fromY];
    int empty = -1;
    if (currentPlayer != space.piece.player)
    {
        return FALSE;
    }
    if (space.empty || (fromX == toX && fromY == toY))
        return 0;                                 //"No piece to access. Please move an actual piece." || "Invalid move. Same position.";
    empty = fetchMovement(space.piece, toX, toY); // Liberamos la pos de from
    if (empty == 3)
    {
        space.empty = empty;
        return 3;
    }
    space.empty = empty;
    return 1;
}

static int fetchMovement(t_piece piece, int toX, int toY)
{
    int mov = -1;
    //Verifico que la pieza seleccionada sea del jugador del turno. En caso contrario se retorna que no puede hacerse un movimiento.

    switch (piece.name)
    {
    case PAWN:
        mov = pawn(piece, toX, toY);
        break;
    case ROOK:
        mov = rook(piece, toX, toY);
        break;
    case BISHOP:
        mov = bishop(piece, toX, toY);
        break;
    case QUEEN:
        mov = queen(piece, toX, toY);
        break;
    case KING:
        mov = king(piece, toX, toY);
        break;
    case KNIGHT:
        mov = knight(piece, toX, toY);
        break;

    default:
        break;
    }
    int flag = mov == 0; //si es cero, es que puede moverse
    if (flag)
    {
        move(piece, toX, toY);
    }
    if (mov == 3)
        return mov; //caso en que mato al rey
    return !flag;
}

void startTimer(int player)
{
    (player == PLAYER1) ? (timer_player1 = 0) : (timer_player2 = 0);
    // syscall.
    _timerFunc(&activeTimer, TRUE);
}

void endTimer()
{
    timer_player1 = 0;
    timer_player2 = 0;
    _timerFunc(&activeTimer, FALSE);
}
void pauseTimer()
{
    _timerFunc(&activeTimer, FALSE);
}
void resumeTimer()
{
    _timerFunc(&activeTimer, TRUE);
}
// Funcion pasada por parametro encargada de actualizar los contadores de tiempo.
void activeTimer()
{
    if (currentPlayer == PLAYER1)
    {
        timer_player1++;
    }
    else if (currentPlayer == PLAYER2)
    {
        timer_player2++;
    }
}
// Funcion nueva que lee input del teclado.
int readPlayerInput(char *inputBuffer, int maxSize, char token)
{
    int size = 0;
    uint64_t c;
    while (size < (maxSize - 1) && (c = getChar()) != '\n' && c != token)
    {

        if (c && c != '\t') // Verificamos que se presiona una letra. No permitimos tabs en esta consola porque romperia con las dimensiones predeterminadas.
        {
            if (c == 'r')
            {
                rotate();
            }
            else if (c != '\b')
            {
                displayChar(c);
                inputBuffer[size++] = c;
            }
            else if (size > 0)
            {
                displayChar('\b');
                size--;
            }
        }
        else
        { // Se hace un update en el timer visual para que el jugador vea el tiempo que lleva.
            int time = (currentPlayer == PLAYER1 ? timer_player1 : timer_player2);
            if (time % TIMER_TICKS_PER_SEC == 0)
            {
                // printInt(time/TIMER_TICKS_PER_SEC);
                updateTimerConsole(time / TIMER_TICKS_PER_SEC);
            }
            int lastTimer = (currentPlayer == PLAYER2 ? timer_player1 : timer_player2);
            if ((time / TIMER_TICKS_PER_SEC) - lastTimer >= 60)
            {
                return -1;
            }
        }
    }
    // Ponemos la marca de final al string.
    inputBuffer[size++] = 0;
    if (c == '\n')
    {
        char aux[size];
        memcpy(aux, inputBuffer, size);
        int processResult = processGame(inputBuffer);
        if (processResult == 1)
        {
            printLogLine(aux, currentPlayer);
            endTimer(currentPlayer);
            if (!skip_turn)
                (currentPlayer == PLAYER1) ? (currentPlayer = PLAYER2) : (currentPlayer = PLAYER1);
            startTimer(currentPlayer);
            printPlayer(currentPlayer, LAST_LINE);
        }
        else if (processResult == 0)
        {
            clearLine(LAST_LINE);
            printPlayer(currentPlayer, LAST_LINE);
            resetCursor();
        }
        else // == 3 : Hacke mate.
        {
            return 3;
        }
    }

    return c == token;
}

/****Inicializamos piezas y tablero *****/

static void initializeBoard()
{
    for (int j = 0; j < 8; j++)
    {
        //Se ponen los peones primero con sus respectivos colores y posiciones.
        board[j][1].empty = FALSE;
        board[j][6].empty = FALSE;
        board[j][1].piece = initializePiece(j, 1, PAWN, WHITE, PLAYER1);
        board[j][6].piece = initializePiece(j, 6, PAWN, BLACK, PLAYER2);
    }
    //Se ponen las torres
    board[0][0].empty = FALSE;
    board[0][7].empty = FALSE;
    board[0][0].piece = initializePiece(0, 0, ROOK, WHITE, PLAYER1);
    board[0][7].piece = initializePiece(0, 7, ROOK, BLACK, PLAYER2);
    board[7][0].empty = FALSE;
    board[7][7].empty = FALSE;
    board[7][0].piece = initializePiece(7, 0, ROOK, WHITE, PLAYER1);
    board[7][7].piece = initializePiece(7, 7, ROOK, BLACK, PLAYER2);

    //Se ponen los caballos
    board[1][0].empty = FALSE;
    board[1][7].empty = FALSE;
    board[1][0].piece = initializePiece(1, 0, KNIGHT, WHITE, PLAYER1);
    board[1][7].piece = initializePiece(1, 7, KNIGHT, BLACK, PLAYER2);
    board[6][0].empty = FALSE;
    board[6][7].empty = FALSE;
    board[6][0].piece = initializePiece(6, 0, KNIGHT, WHITE, PLAYER1);
    board[6][7].piece = initializePiece(6, 7, KNIGHT, BLACK, PLAYER2);

    //Se ponen los alfiles
    board[2][0].empty = FALSE;
    board[2][7].empty = FALSE;
    board[2][0].piece = initializePiece(2, 0, BISHOP, WHITE, PLAYER1);
    board[2][7].piece = initializePiece(2, 7, BISHOP, BLACK, PLAYER2);
    board[5][0].empty = FALSE;
    board[5][7].empty = FALSE;
    board[5][0].piece = initializePiece(5, 0, BISHOP, WHITE, PLAYER1);
    board[5][7].piece = initializePiece(5, 7, BISHOP, BLACK, PLAYER2);

    //Se pone a la reina
    board[3][0].empty = FALSE;
    board[3][7].empty = FALSE;
    board[3][0].piece = initializePiece(3, 0, QUEEN, WHITE, PLAYER1);
    board[3][7].piece = initializePiece(3, 7, QUEEN, BLACK, PLAYER2);

    //Se pone al rey
    board[4][0].empty = FALSE;
    board[4][7].empty = FALSE;
    board[4][0].piece = initializePiece(4, 0, KING, WHITE, PLAYER1);
    board[4][7].piece = initializePiece(4, 7, KING, BLACK, PLAYER2);

    //Se inicializan los espacios vacios de la matriz logica
    for (int i = 2; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[j][i].empty = TRUE;
            board[j][7 - i].empty = TRUE;
        }
    }
}

//inializamos una pieza con los datos pasados
static t_piece initializePiece(int posX, int posY, typePieces name, int color, int player)
{
    t_piece piece;
    piece.player = player;
    piece.name = name;
    piece.color = color;
    piece.posX = posX;
    piece.posY = posY;
    piece.moved = FALSE;
    return piece;
}

void drawBoard(int x, int y)
{
    char square[] = "X";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) // ambos pares o ambos impares
                _drawFigure(square, BEIGE, TILE, x + i * TILE, y + j * TILE);
            else
                _drawFigure(square, BROWN, TILE, x + i * TILE, y + j * TILE);
        }
    }
    for (int k = 0; k < 8; k++)
    {
        _drawFigure(square, BLACK, TILE, x + 7 * TILE + TILE, y + k * TILE);
    }
}

static void drawPieces(int x, int y)
{
    //extern void _drawFigure(char *toDraw, int color, int size, int x, int y);
    int piece, color;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].empty == FALSE)
            {
                piece = board[i][j].piece.name;
                color = board[i][j].piece.color;
                //_drawFigure(piecesBitmap(piece), color, 5, x + i * TILE, y + j * TILE);
                drawFigure(piece, color, i, j, x, y);
            }
        }
    }
}

//************* MOVIMIENTOS ***********//
int attack(t_piece fromPiece, t_piece toPiece)
{
    t_tile toTile = getTile(toPiece.posX, toPiece.posY);
    if (fromPiece.player != toPiece.player)
    {
        if (toPiece.name == KING || jaqueP1 == 3 || jaqueP2 == 3) 
        {
            return 3;
        }
        deleteFigure(toTile.piece);
        toTile.empty = TRUE; //dejo libre el casillero al que voy asi puedo moverme
        return 0;
    }
    else
        return 1;
}

//Buscamos al rey contrario
static void findKing(int player, int *posXK, int *posYK, int *col)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].piece.name == KING && board[i][j].piece.player != player)
            {
                *posXK = i;
                *posYK = j;
                *col = board[i][j].piece.color;
                return;
            }
        }
    }
}

//Prevee si puede hacer un jaque con el movimiento que esta haciendo
static int prevJaque(t_piece fromPiece, int *posXK, int *posYK, int *col)
{
    int posX, posY, color, jaq;
    findKing(fromPiece.player, &posX, &posY, &color);
    *posXK = posX, *posYK = posY, *col = color;

    switch (fromPiece.name)
    {
    case PAWN:
        jaq = pawn(fromPiece, posX, posY);
        break;
    case ROOK:
        jaq = rook(fromPiece, posX, posY);
        break;
    case BISHOP:
        jaq = bishop(fromPiece, posX, posY);
        break;
    case QUEEN:
        jaq = queen(fromPiece, posX, posY);
        break;
    case KING:
        jaq = king(fromPiece, posX, posY);
        break;
    case KNIGHT:
        jaq = knight(fromPiece, posX, posY);
        break;

    default:
        break;
    }
    //si es cero, es que puede moverse y hacer un jaque
    return jaq;
}

static void deleteFigure(t_piece piece)
{
    if ((piece.posX % 2 == 0 && piece.posY % 2 == 0) || (piece.posX % 2 == 1 && piece.posY % 2 == 1))
    {
        drawFigure(EMPTY, BEIGE, piece.posX, piece.posY, MAX_WIDTH, 0);
        //_drawFigure(piecesBitmap(EMPTY), BEIGE, 5, MAX_WIDTH + piece.posX *TILE, piece.posY *TILE);
    }
    else
    {
        drawFigure(EMPTY, BROWN, piece.posX, piece.posY, MAX_WIDTH, 0);
        //_drawFigure(piecesBitmap(EMPTY), BROWN, 5, MAX_WIDTH + piece.posX * TILE, piece.posY * TILE);
    }
}

static void move(t_piece piece, int toX, int toY)
{
    board[piece.posX][piece.posY].empty = TRUE;
    deleteFigure(piece);
    piece.posX = toX;
    piece.posY = toY;
    piece.moved = TRUE;
    board[toX][toY].piece = piece;
    board[toX][toY].empty = FALSE;
    drawFigure(piece.name, piece.color, piece.posX, piece.posY, MAX_WIDTH, 0);
    //_drawFigure(piecesBitmap(piece.name), piece.color, 5, MAX_WIDTH+ toX * TILE, toY * TILE);

    int posXK, posYK, col;
    int prev = prevJaque(piece, &posXK, &posYK, &col);

    if (prev == 0 )
    {
        if (piece.player == PLAYER1){
            jaqueP1++;
            printIn("Check P1.",MAX_WIDTH + CHAR_WIDTH*2,LAST_LINE, YELLOW);
        }
        else{
            jaqueP2++;
            printIn("Check P2.",MAX_WIDTH + CHAR_WIDTH*2,LAST_LINE, YELLOW);
        }
        
        drawFigure(KING, col, posXK, posYK, MAX_WIDTH, 0);
    }
}

//utilizamos para traer un casillero
static t_tile getTile(int x, int y)
{
    t_tile toReturn = board[x][y];
    return toReturn;
}

//Si esta en su extremo correspondiente el peon puede cambiarse a otra pieza
void coronation(t_piece fromPiece, typePieces toName, int toX, int toY)
{
    deleteFigure(fromPiece);
    board[fromPiece.posX][fromPiece.posY].empty = TRUE;
    fromPiece.posX = toX;
    fromPiece.posY = toY;
    fromPiece.moved = TRUE;
    board[toX][toY].piece = fromPiece;
    board[toX][toY].empty = FALSE;
    drawFigure(toName, fromPiece.color, toX, toY, MAX_WIDTH, 0);
    //_drawFigure(piecesBitmap(toName), fromPiece.color, 5, MAX_WIDTH+ toX * TILE, toY * TILE);
}

void enroque(int lon)
{
    //solo si las torres y la reina estan en posiciones iniciales
    //lon sirve por si aun no se movieron las 2 torres y el user elije que enroque hacer
    t_piece ROOK1P1 = board[0][0].piece, ROOK2P1 = board[7][0].piece, kingP1 = board[4][0].piece; //piezas del jug 1
    t_piece ROOK1P2 = board[0][7].piece, ROOK2P2 = board[7][7].piece, kingP2 = board[4][7].piece; //piezas del jug 2

    int empty = -1;
    int fromX, fromY;

    if ((board[0][0].empty == FALSE || board[7][0].empty == FALSE) && board[4][0].empty == FALSE && currentPlayer == PLAYER1)
    {
        if (ROOK1P1.moved == FALSE && kingP1.moved == FALSE)
        {
            //vemos de izquierda a derecha, torre 1 es en A1 y torre 2 es en H1
            if (lon == 2)
            { //enroque corto
                fromX = ROOK2P1.posX;
                fromY = ROOK2P1.posY;
                empty = rook(ROOK2P1, fromX + lon, fromY);
                if (empty == FALSE)
                {
                    move(ROOK2P1, 7 - lon, 0);
                    move(kingP1, 4 + 2, 0);
                }
            }
            if (lon == 3)
            { //enroque largo
                empty = rook(ROOK1P1, 7 - lon, 0);

                if (empty == FALSE)
                {
                    move(ROOK1P1, 0 + lon, 0);
                    move(kingP1, 4 - 2, 0);
                }
            }
        }
    }
    //para el jugador 2
    else
    {
        if ((board[0][7].empty == FALSE || board[7][7].empty == FALSE) && board[4][7].empty == FALSE && currentPlayer == PLAYER2)
        {
            if (ROOK1P2.moved == FALSE && kingP2.moved == FALSE)
            {
                //vemos de izquierda a derecha, torre 1 es en A8 y torre 2 es en H8
                if (lon == 2)
                { //enroque corto
                    empty = rook(ROOK2P2, 7 - lon, 7);

                    if (empty == FALSE)
                    {
                        move(ROOK2P2, 7 - lon, 7);
                        move(kingP2, 4 + 2, 7);
                    }
                }
                if (lon == 3)
                { //enroque largo
                    empty = rook(ROOK1P2, 0 + lon, 7);

                    if (empty == FALSE)
                    {
                        move(ROOK1P2, 0 + lon, 7);
                        move(kingP2, 4 - 2, 7);
                    }
                }
            }
        }
    }
}

int checkPeonAlPaso(t_piece piece, int toX, int toY)
{
    t_tile neighbour1;
    t_tile neighbour2;
    t_tile aux = {{0, EMPTY, 0, 0, 0, 0}, TRUE};
    if (toX - 1 < 0)
    {
        neighbour1 = aux;
    }
    else
    {
        neighbour1 = getTile(toX - 1, toY);
    }
    if (toX + 1 > 7)
    {
        neighbour2 = aux;
    }
    else
    {
        neighbour2 = getTile(toX + 1, toY);
    }

    t_tile neighbours[] = {neighbour1, neighbour2};
    for (int i = 0; i < 2 && !skip_turn; i++)
    {
        t_tile neighbour = neighbours[i];
        if (neighbour.empty == FALSE && neighbour.piece.name == PAWN && neighbour.piece.player != piece.player)
        {
            //Se elimino el peon que sufre la jugada y se le avisa al espacio que queda libre
            deleteFigure(piece);
            t_tile fromTile = getTile(piece.posX, piece.posY);
            fromTile.empty = TRUE;
            //Se mueve obligatoriamente al peon contrario para que ejecute el peon al paso.
            int where_to_moveY = fromTile.piece.color == WHITE ? neighbour.piece.posY - 1 : neighbour.piece.posY + 1;
            move(neighbour.piece, piece.posX, where_to_moveY);
            neighbour.empty = TRUE;
            skip_turn = TRUE;
        }
    }
    return skip_turn; //es decir que si se ejecuto el peon al paso debo decir que ese espacio no esta libre para que no se ejecute el move.
}

//vemos si estan vacios los casilleros entre medio hacia adelante y atras, dependiendo el movimiento
//1 es que no pude moverme, 0 que si
static int isEmptyP(int fromX, int fromY, int toX, int toY)
{
    for (int j = 1; fromY + j <= toY; j++)
    {
        if (board[fromX][fromY + j].empty == FALSE)
        {
            return 1;
        }
    }
    return 0;
}

static int isEmptyN(int fromX, int fromY, int toX, int toY)
{
    for (int j = 1; fromY - j >= toY; j++)
    {
        if (board[fromX][fromY - j].empty == FALSE)
        { //&& board[i][j].piece.posX != toX &&  board[i][j].piece.posY != toY
            return 1;
        }
    }
    return 0;
}

//************* PIEZAS ***********//

int pawn(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    int empty = -1;
    t_tile toTile;

    if (fromPiece.player == PLAYER1)
    {
        if (fromY > toY)
        {
            return empty;
        }
        //si el movimiento es en diagonal solo si hay una pieza a comer o al paso, sino es ilegal
        if (fromX != toX)
        {
            if (toX == fromX + 1 && toY == fromY + 1)
            {
                toTile = getTile(toX, toY);
                if (toTile.empty == FALSE)
                {
                    empty = attack(fromPiece, toTile.piece);
                    return empty;
                }
            }
            if (toX == fromX - 1 && toY == fromY + 1)
            {
                toTile = getTile(toX, toY);
                if (toTile.empty == FALSE)
                {
                    empty = attack(fromPiece, toTile.piece);
                    return empty;
                }
            }
        }
        //si el movimiento es recto
        else
        {
            if (toY == fromY + 2 && fromPiece.moved == FALSE)
            {
                //miro si los 2 de adelante estan libres
                empty = isEmptyP(fromX, fromY, toX, toY);
                //aca se hace la verificacion del peon al paso y se elimina esta misma pieza si tengo al lado un peon enemigo (izq y derecha)
                if (empty == 0)
                { //el espacio debe estar vacio.
                    empty = checkPeonAlPaso(fromPiece, toX, toY);
                }
            }
            else
            {
                if (toY == FINAL_ROW && toCoronation != 6)
                {
                    coronation(fromPiece, toCoronation, toX, toY);
                    return -1;
                }
                if (toY == fromY + 1)
                {
                    empty = isEmptyP(fromX, fromY, toX, toY);
                }
            }
        }
    }
    //analizo el juegador 2
    else
    {
        if (fromY < toY)
            return empty;
        //si el movimiento es en diagonal
        if (fromX != toX)
        {
            if (toX == fromX + 1 && toY == fromY - 1)
            {
                //come en diagonal si esta ocupado
                toTile = getTile(toX, toY);
                if (toTile.empty == FALSE)
                {
                    empty = attack(fromPiece, toTile.piece);
                    return empty;
                }
            }
            if (toX == fromX - 1 && toY == fromY - 1)
            {
                toTile = getTile(toX, toY);
                if (toTile.empty == FALSE)
                {
                    empty = attack(fromPiece, toTile.piece);
                    return empty;
                }
            }
        }
        //si el movimiento es recto
        else
        {
            if (toY == fromY - 2 && fromPiece.moved == FALSE)
            { //miro si los 2 tile de las filas adelante estan vacias
                empty = isEmptyN(fromX, fromY, toX, toY);
                if (empty == 0)
                { //el espacio debe estar vacio.
                    empty = checkPeonAlPaso(fromPiece, toX, toY);
                }
                return empty;
            }
            else
            {
                if (toY == FIRST_ROW && toCoronation != 6)
                {
                    coronation(fromPiece, toCoronation, toX, toY);
                    return -1;
                }
                if (toY == fromY - 1)
                {
                    empty = isEmptyN(fromX, fromY, toX, toY);
                    return empty;
                }
            }
        }
    }
    return empty;
}

int rook(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    t_tile toTile = getTile(toX, toY);
    int empty = -1, i;

    if (fromX == toX)
    {
        if (fromY < toY)
        { //abajo
            for (i = 1; fromY + i < toY; i++)
            {
                if (board[fromX][fromY + i].empty == FALSE)
                {
                    return 1;
                }
            }
            empty = 0;
        }
        else
        { //arriba
            for (i = 1; fromY - i > toY; i++)
            {
                if (board[fromX][fromY - i].empty == FALSE)
                {
                    return 1;
                }
            }
            empty = 0;
        }
    }
    else
    {
        if (fromY == toY)
        {
            if (fromX < toX)
            { //derecha
                for (i = 1; fromX + i < toX; i++)
                {
                    if (board[fromX + i][fromY].empty == FALSE)
                    {
                        return 1;
                    }
                }
                empty = 0;
            }
            else
            { //izquierda
                for (i = 1; fromX - i > toX; i++)
                {
                    if (board[fromX - i][fromY].empty == FALSE)
                    {
                        return 1;
                    }
                }
                empty = 0;
            }
        }
    }

    if (toTile.empty == TRUE && empty == FALSE)
    { //pude recorrer y si tambien esta vacio el ultimo, movete
        return 0;
    }
    else
    {
        if (toTile.empty == FALSE && empty == FALSE)
        { //pudo recorrer y mira el ultimo a ver si puede comer
            empty = attack(fromPiece, toTile.piece);
        }
    }

    return empty;
}

int bishop(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    t_tile toTile = getTile(toX, toY);

    int empty = -1, i;
    if (toX - fromX == toY - fromY)
    { // ambos pos o neg
        if (toX > fromX)
        { //  hacia la derecha y abajo
            for (i = 1; fromX + i < toX && fromY + i < toY; i++)
            {
                if (board[fromX + i][fromY + i].empty != TRUE)
                {
                    return 1;
                }
            }
            empty = 0;
        }
        else
        { // hacia izquierda arriba
            for (i = 1; fromX - i > toX && fromY - i > toY; i++)
            {
                if (board[fromX - i][fromY - i].empty != TRUE)
                {
                    return 1;
                }
            }
            empty = 0;
        }
    }
    else
    {
        if (-(toX - fromX) == toY - fromY)
        {
            if (toX > fromX)
            { // hacia la derecha y arriba
                for (i = 1; fromX + i < toX && fromY - i > toY; i++)
                {
                    if (board[fromX + i][fromY - i].empty != TRUE)
                    {
                        return 1;
                    }
                }
                empty = 0;
            }
            else
            { // hacia la izquierda abajo
                for (i = 1; fromX - i > toX && fromY + i < toY; i++)
                {
                    if (board[fromX - i][fromY + i].empty != TRUE)
                    {
                        return 1;
                    }
                }
                empty = 0;
            }
        }
    }
    if (toTile.empty == FALSE && empty == FALSE)
    {
        empty = attack(fromPiece, toTile.piece);
    }
    else
    {
        if (toTile.empty == TRUE && empty == FALSE)
        {
            return 0;
        }
    }
    return empty;
}

int king(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    int empty = -1;

    if ((toY == fromY && (toX == fromX + 1 || toX == fromX - 1)) || (toX == fromX && (toY == fromY + 1 || toY == fromY - 1)))
    {
        empty = rook(fromPiece, toX, toY);
    }
    else
    {
        if (((toX == fromX + 1) || (toX == fromX - 1)) && ((toY == fromY + 1) || (toY == fromY - 1)))
            empty = bishop(fromPiece, toX, toY);
    }

    return empty;
}

int queen(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    int empty = -1;

    if (toX == fromX || fromY == toY)
    {
        empty = rook(fromPiece, toX, toY);
    }
    else
    {
        if (abs(toX - fromX) == abs(toY - fromY))
        {
            empty = bishop(fromPiece, toX, toY);
        }
    }

    return empty;
}

int knight(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    int empty = -1;

    int potentialMoves[8][2] = {
        {fromX + 1, fromY - 2},
        {fromX + 2, fromY - 1},
        {fromX - 1, fromY - 2},
        {fromX - 2, fromY - 1},
        {fromX + 1, fromY + 2},
        {fromX + 2, fromY + 1},
        {fromX - 1, fromY + 2},
        {fromX - 2, fromY + 1},
    };
    t_tile tile = board[toX][toY];

    for (int j = 0; j < 8; j++)
    {
        if (toX == potentialMoves[j][0] && toY == potentialMoves[j][1])
        {
            if (tile.empty != FALSE)
            {
                return 0;
            }
            else
            {
                empty = attack(fromPiece, tile.piece);
                return empty;
            }
        }
    }
    return empty;
}
void rotate()
{
    rotation++;
    drawBoard(MAX_WIDTH, 0);
    printCoord();
    drawPieces(MAX_WIDTH, 0);
}
void drawFigure(int piece, int color, int i, int j, int fromWhereX, int fromWhereY)
{
    switch (rotation % 4)
    {
    case 0:
        _drawFigure(piecesBitmap(piece), color, 5, fromWhereX + i * TILE, fromWhereY + j * TILE);
        break;
    case 1:
        _drawFigure(piecesBitmap(piece), color, 5, fromWhereX + j * TILE, fromWhereY + i * TILE);
        break;
    case 2:
        _drawFigure(piecesBitmap(piece), color, 5, fromWhereX + (7 - i) * TILE, fromWhereY + (7 - j) * TILE);
        break;
    case 3:
        _drawFigure(piecesBitmap(piece), color, 5, fromWhereX + (7 - j) * TILE, fromWhereY + (7 - i) * TILE);
        break;
    }
}
void printCoord()
{
    char *c[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    char numToPrint[2];
    for (int i = 0; i < 8; i++)
    {
        uintToBase(i + 1, numToPrint, 10);
        switch (rotation % 2)
        {
        case 0:
            // Numeros
            printIn(c[i], (MAX_WIDTH / CHAR_WIDTH) + 7 + i * (TILE / CHAR_WIDTH), LAST_LINE - 4, BROWN);
            // Letras.
            printIn(numToPrint, (MAX_WIDTH / CHAR_WIDTH) - 2, i * (TILE / CHAR_HEIGHT) + 3, BEIGE);
            break;
        case 1:
            // Numeros
            printIn(numToPrint, (MAX_WIDTH / CHAR_WIDTH) + 7 + i * (TILE / CHAR_WIDTH), LAST_LINE - 4, BROWN);
            // Letras.
            printIn(c[i], (MAX_WIDTH / CHAR_WIDTH) - 2, i * (TILE / CHAR_HEIGHT) + 3, BEIGE);
            break;
        }
    }
}