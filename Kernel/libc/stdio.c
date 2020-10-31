/**
 * stdio.c: Librería dedicada a la impresión y manejo de salida a pantalla.
*/
#include <stdio.h>

int height = HEIGHT / CHAR_HEIGHT, width = WIDTH / CHAR_WIDTH;
int x = 0, y = (HEIGHT/CHAR_HEIGHT)-FONT_SIZE, blink = 0;

void backspace();
void enter();
void tab();
void blinkCursor();

void setCursor(unsigned int new_x, unsigned int new_y)
{
    if (new_x > width || new_x < 0 || new_y > height || new_y < 0)
        return;
    x = new_x;
    y = new_y;
    blinkCursor();
}

void blinkCursor() {
    drawCursor(x * CHAR_WIDTH, y * CHAR_HEIGHT, blink = !blink);
}

void putchar(char c)
{
    switch (c)
    {
    case '\n':
        enter();
        break;
    case '\b':
        backspace();
        break;
    case '\t':
        tab();
        break;
    default:
        // Se debe ver si saltar de linea o quedarse en la misma.
        drawChar(x*CHAR_WIDTH, y*CHAR_HEIGHT, c, FONT_SIZE, WHITE, BLACK);
        ((x += FONT_SIZE) > width) ? enter() : setCursor(x, y);
    }
}

uint64_t sWrite(char *buffer, int size)
{
    while (size-- && *buffer != 0)
    {
        putchar(*buffer);
        buffer++;
    }
    return size == 0;
}

void backspace()
{
    if (x == 0 && y == 0)
        return;
    setCursor(x-FONT_SIZE, y);
    putchar(' ');
    if (blink)
    {
        blinkCursor();
    }
    x-=FONT_SIZE;
}

void enter()
{
    if (blink)
    {
        blinkCursor();
    }
    (y < height) ? scrollUpScreen() : clearScreen();
    setCursor(0, y); 
}

void tab()
{
    ((x += (4 * FONT_SIZE)) < width) ? setCursor(x, y) : enter();
}