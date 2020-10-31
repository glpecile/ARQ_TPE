#include <videoDriver.h>

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

/**
 * Dibuja un pixel en la pantalla.
 */
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

	char bitIsPresent;

	unsigned char *toDraw = charBitmap(character); // consigue la letra de la estructura en font.c

	for (int i = 0; i < CHAR_HEIGHT; i++)
	{
		for (int j = 0; j < CHAR_WIDTH; j++)
		{
			bitIsPresent = (1 << (CHAR_WIDTH - j)) & toDraw[i]; // desenmascaramos.

			if (bitIsPresent)
				drawPixel(aux_x, aux_y, fontColor); // dibuja la letra.
			else 
				drawPixel(aux_x, aux_y, bgColor); // dibuja el fondo.

			aux_x += fontSize; // incrementa en x el tamaño.
		}
		aux_x = x;
		aux_y += fontSize; // incrementa en y el tamaño.
	}
}

// ver si sirve para el ajedrez.
void drawRectangle(unsigned int x, unsigned int y, int b, int h, int color)
{
	for (int i = 0; i < b; i++)
	{
		for (int j = 0; j < h; j++)
		{
			drawPixel(x + i, y + j, color);
		}
	}
}

// idem drawRectangle.
void drawSquare(unsigned int x, unsigned int y, int l, int color)
{
	drawRectangle(x, y, l, l, color);
}

void drawCursor(int x, int y, int blink)
{
	blink ? drawChar(x, y, '|', 1, GREEN, BLACK) : drawChar(x, y, ' ', 1, BLACK, BLACK);
}

void scrollUpScreen()
{
	int length = (screenData->width * screenData->height * PIXEL) - ((PIXEL * screenData->width) * CHAR_HEIGHT);
	memcpy((void *)(uint64_t)(screenData->framebuffer), 
	(void *)(uint64_t)(screenData->framebuffer + (PIXEL * screenData->width) * CHAR_HEIGHT), 
	length);
	clearLine();
}

void clearLine() {
	int width = screenData->width;
	int height = screenData->height;
	for (int i = 0; i < width; i+=CHAR_WIDTH)
	{
		drawChar(i,height-CHAR_HEIGHT,' ',1,BLACK,BLACK);
	}
}

void clearScreen()
{
	int width = screenData->width;
	int height = screenData->height;
	for (int i = 0; i < height ; i++)
	{
		for (int j = 0; j < width; j++)
		{
			drawPixel(i, j, BLACK);
		}
		
	}
}