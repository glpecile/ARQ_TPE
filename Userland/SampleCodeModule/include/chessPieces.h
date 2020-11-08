/**
 * chessPieces.h: Contrato para imprimir piezas de ajedrez.
 */ 
#ifndef __chessPieces_H_
#define __chessPieces_H_
#define PIECE_HEIGHT 14
#define PIECE_WIDTH 14
char * piecesBitmap(int c);
typedef enum
{
    PAWN = 0,
    ROOK = 1,
    KNIGHT = 2,
    BISHOP = 3,
    QUEEN = 4,
    KING = 5,
    EMPTY = 6
} typePieces;

/**
 * Matriz de chars para imprimir las piezas.
// 0: Peon.
    "
    ______________\n
    ______________\n
    ______________\n
    ______________\n
    _____XXXX_____\n
    ____XXXXXX____\n
    _____XXXX_____\n
    ___XXXXXXXX___\n
    _____XXXX_____\n
    _____XXXX_____\n
    _____XXXX_____\n
    ____XXXXXX____\n
    __XXXXXXXXXX__\n
    ______________
    ",
    // 1: Torre.
    "
    ______________\n
    ______________\n
    _XXX__XX__XXX_\n
    _XXXXXXXXXXXX_\n
    _XXXXXXXXXXXX_\n
    _XXXXXXXXXXXX_\n
    ___XXXXXXXX___\n
    ___XXXXXXXX___\n
    ___XXXXXXXX___\n
    ___XXXXXXXX___\n
    ___XXXXXXXX___\n
    _XXXXXXXXXXXX_\n
    _XXXXXXXXXXXX_\n
    ______________
    ",
    // 2: Caballo.
    "_____________\n
    ___XX__XXX____\n
    _XXXXXXXXXXX__\n
    XXXXXXXXX_XXX_\n
    XXXXXX_XXXXXXX\n
    XXXXXX___XXXXX\n
    XXXXXXXX______\n
    _XXXXXXXXX____\n
    __XXXXXXXXX___\n
    __XXXXXXXXXX__\n
    _XXXXXXXXXXXX_\n
    _XXXXXXXXXXXX_\n
    _XXXXXXXXXXXX_\n
    ______________
    ",
    // 3: Alfil.
    "
    ______________\n
    _______X______\n
    _____XXXX_____\n
    ____X_XXXX____\n
    ___XXX_XXXX___\n
    ____XXX_XX____\n
    ______XX______\n
    ______XX______\n
    _____XXXX_____\n
    _____XXXX_____\n
    ___XXXXXXXX___\n
    ___XXXXXXXX___\n
    __XXXXXXXXXX__\n
    ______________
    ",
    // 4: Reina.
    "
    ______XX______\n
    _____XXXX_____\n
    ______XX______\n
    ____XXXXXX____\n
    ___X_XXXX_X___\n
    ____XXXXXX____\n
    ______XX______\n
    ______XX______\n
    _____XXXX_____\n
    _____XXXX_____\n
    ____XXXXXX____\n
    ___XXXXXXXX___\n
    __XXXXXXXXXX__\n
    ______________
    ",
    // 5: Rey.
    "
    ______________\n
    ______XX______\n
    ____XXXXXX____\n
    ______XX______\n
    ___XXXXXXXX___\n
    ____X_XX_X____\n
    _____XXXX_____\n
    ______XX______\n
    _____XXXX_____\n
    _____XXXX_____\n
    ___XXXXXXXX___\n
    ___XXXXXXXX___\n
    __XXXXXXXXXX__\n
    ______________
    "
*/
#endif