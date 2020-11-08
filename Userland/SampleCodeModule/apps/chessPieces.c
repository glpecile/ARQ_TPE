/**
 * chessPieces.c: Similar a font.c para piezas de ajedrez.
 * El kernel no debe por qué saber que es una pieza de ajedrez
 * pero debe poder dibujar una figura genérica si se lo requiere.
 */
#include <chessPieces.h>

// Arreglar, problema con matriz.
static char *__pieces_bitmap__[] = {
    // 0: Peon.
    "______________\n______________\n______________\n______________\n_____XXXX_____\n____XXXXXX____\n_____XXXX_____\n___XXXXXXXX___\n_____XXXX_____\n_____XXXX_____\n_____XXXX_____\n____XXXXXX____\n__XXXXXXXXXX__\n______________",
    // 1: Torre.
    "______________\n______________\n_XXX__XX__XXX_\n_XXXXXXXXXXXX_\n_XXXXXXXXXXXX_\n_XXXXXXXXXXXX_\n___XXXXXXXX___\n___XXXXXXXX___\n___XXXXXXXX___\n___XXXXXXXX___\n___XXXXXXXX___\n_XXXXXXXXXXXX_\n_XXXXXXXXXXXX_\n______________",
    // 2: Caballo.
    "_____________\n___XX__XXX____\n_XXXXXXXXXXX__\nXXXXXXXXX_XXX_\nXXXXXX_XXXXXXX\nXXXXXX___XXXXX\nXXXXXXXX______\n_XXXXXXXXX____\n__XXXXXXXXX___\n__XXXXXXXXXX__\n_XXXXXXXXXXXX_\n_XXXXXXXXXXXX_\n_XXXXXXXXXXXX_\n______________",
    // 3: Alfil.
    "______________\n_______X______\n_____XXXX_____\n____X_XXXX____\n___XXX_XXXX___\n____XXX_XX____\n______XX______\n______XX______\n_____XXXX_____\n_____XXXX_____\n___XXXXXXXX___\n___XXXXXXXX___\n__XXXXXXXXXX__\n______________",
    // 4: Reina.
    "______XX______\n_____XXXX_____\n______XX______\n____XXXXXX____\n___X_XXXX_X___\n____XXXXXX____\n______XX______\n______XX______\n_____XXXX_____\n_____XXXX_____\n____XXXXXX____\n___XXXXXXXX___\n__XXXXXXXXXX__\n______________",
    // 5: Rey.
    "______________\n______XX______\n____XXXXXX____\n______XX______\n___XXXXXXXX___\n____X_XX_X____\n_____XXXX_____\n______XX______\n_____XXXX_____\n_____XXXX_____\n___XXXXXXXX___\n___XXXXXXXX___\n__XXXXXXXXXX__\n______________",
    // 6: Vacio.
    "XXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX\nXXXXXXXXXXXXXX"};

char *piecesBitmap(int c)
{
    return __pieces_bitmap__[c];
}
