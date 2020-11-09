/**
 * videoDriver.c: Driver encargado del manejo de la pantalla como recurso protegido.
*/
#include <videoDriver.h>

// para testeo
#include <stdio.h>

struct vbe_mode_info_structure
{
	uint16_t attributes;  // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;	  // deprecated
	uint8_t window_b;	  // deprecated
	uint16_t granularity; // deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;		   // number of bytes per horizontal line
	uint16_t width;		   // width in pixels
	uint16_t height;	   // height in pixels
	uint8_t w_char;		   // unused...
	uint8_t y_char;		   // ...
	uint8_t planes;
	uint8_t bpp;   // bits per pixel in this mode
	uint8_t banks; // deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer; // physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__((packed));

struct vbe_mode_info_structure *screenData = (void *)0x5C00;

unsigned getPixelDataByPosition(int x, int y)
{
	return (x + y * screenData->width) * PIXEL;
}

void drawPixel(int x, int y, int color)
{
	char *curpos = ((char *)(uint64_t)screenData->framebuffer);
	unsigned data = getPixelDataByPosition(x, y);
	curpos[data] = color & 255;				// B
	curpos[data + 1] = (color >> 8) & 255;	// G
	curpos[data + 2] = (color >> 16) & 255; // R
}

void drawChar(int x, int y, char character, int fontSize, int fontColor, int bgColor)
{
	int aux_x = x;
	int aux_y = y;
	unsigned char *toDraw = charBitmap(character);
	char isForeground; // Flag para definir si dibujar el fondo o no.

	for (int i = 0; i < CHAR_HEIGHT; i++)
	{
		for (int j = 0; j < CHAR_WIDTH; j++)
		{
			isForeground = (1 << (CHAR_WIDTH - j)) & toDraw[i]; // decalamos para ver qué dibujamos.

			if (isForeground)
				drawPixel(aux_x, aux_y, fontColor); // dibuja la parte de la figura especificada figura.
			else
				drawPixel(aux_x, aux_y, bgColor); // dibuja la parte del fondo de la figura especificado.

			aux_x += fontSize; // incrementa en x el tamaño.
		}
		aux_x = x;
		aux_y += fontSize; // incrementa en y el tamaño.
	}
}
void drawFigure(char *toDraw, int color, int size, int x, int y)
{
	if (x > (screenData->width) && y > (screenData->height))
	{
		return;
	}
	// Guardamos el estado inicial
	int aux_x = x;
	int aux_y = y;
	// recorremos toDraw
	char c = toDraw[0];
	for (int i = 0; c != 0 && aux_x < screenData->width && aux_y < screenData->height; c = toDraw[i++])
	{
		switch (c)
		{
		case '\n': // Proxima posición en y.
			aux_x = x;
			aux_y += size;
			break;
		case '_': // No dibujo.
			aux_x += size;
			break;
		case 'X': // Dibujo.
			drawSquare(aux_x, aux_y, size, color);
			aux_x += size;
			break;
		default:
			c = 0;
			break;
		}
	}
}

void drawRectangle(unsigned int x, unsigned int y, int base, int height, int color)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < base; j++)
		{
			drawPixel(x + j, y + i, color);
		}
	}
}

void drawSquare(unsigned int x, unsigned int y, int area, int color)
{
	drawRectangle(x, y, area, area, color);
}

void drawCursor(int x, int y, int blink, int color)
{
	blink ? drawChar(x, y, '|', 1, color, BLACK) : drawChar(x, y, ' ', 1, BLACK, BLACK);
}

void scrollUpScreen()
{
	int length = (screenData->width * screenData->height * PIXEL) - ((PIXEL * screenData->width) * CHAR_HEIGHT);
	memcpy((void *)(uint64_t)(screenData->framebuffer),
		   (void *)(uint64_t)(screenData->framebuffer + (PIXEL * screenData->width) * CHAR_HEIGHT),
		   length);
	clearLine();
}

void clearLine()
{
	int width = screenData->width;
	int height = screenData->height;
	for (int i = 0; i < width; i += CHAR_WIDTH)
	{
		drawChar(i, height - CHAR_HEIGHT, ' ', 1, BLACK, BLACK);
	}
}

int getPixelHeight()
{
	return screenData->height;
}

int getPixelWidth()
{
	return screenData->width;
}

void clearScreen()
{
	for (int y = 0; y < screenData->height; y++)
	{
		for (int x = 0; x < screenData->width; x++)
		{
			drawPixel(x, y, BLACK);
		}
	}
}