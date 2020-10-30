/**
 * stdio.c: Librería dedicada a la impresión y manejo de salida a pantalla.
*/
#include <stdio.h>

#define WIDTH 1024
#define HEIGHT 768

int x = 0, y = 0;
int height = HEIGHT / CHAR_HEIGHT, width = WIDTH / CHAR_WIDTH;

/**
 * Define una nueva posicón valida para el cursor y lo vuelve a dibujar.
*/
void setCursor(unsigned int new_x, unsigned int new_y);
void backspace();
void enter();
void tab();

void setCursor(unsigned int new_x, unsigned int new_y)
{
    if (new_x > width || new_x < 0 || new_y > height || new_y < 0)
        return;
    x = new_x;
    y = new_y;
    // drawCursor(x, y);
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
        ((x+=FONT_SIZE) >= width) ? setCursor(0, y + 1) : setCursor(x, y);
    }
}

void printString(char *string)
{
    while (*string != 0)
    {
        putchar(*string);
        string++;
    }
}

void printStringln(char *string)
{
    printString(string);
    putchar('\n');
}

void backspace()
{
    if (x == 0 && y == 0)
        return;
    deleteChar(x, y);
}

void enter()
{
    if (y < height)
    {
        scrollUpScreen();
        setCursor(x, y - FONT_SIZE);
    }
    else
    {
        clearScreen();
    }
}

void tab()
{
    ((x += (4*FONT_SIZE)) <= width) ? setCursor(x, y) : enter();
}
