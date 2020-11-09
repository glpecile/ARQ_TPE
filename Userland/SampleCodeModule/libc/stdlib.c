/**
 * stdlib.c: Libería estandar del usuario.
 */
#include <stdlib.h>

static char buffer[64] = {'0'};

uint64_t getChar()
{
	return _sGetChar();
}

void putChar(char c)
{
	_swrite(&c, 1, WHITE); // Recibe de a una letra, su long es 1 siempre
}

void print(char *s)
{
	int lenght = strlen(s); // Buscamos el largo.
	_swrite(s, lenght, WHITE);
}

void printWithColor(char *string, int color)
{
	int len = strlen(string);
	_swrite(string, len, color);
}

int scan(char *buffer, int size)
{
	char c = 0;
	int len = 0;
	while ((c = getChar()) != '\n' && len < size)
	{
		putChar(c);
		buffer[len] = c;
		len++;
	}
	buffer[len] = '\0';
	return len;
}

void *memcpy(void *destination, const void *source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *)destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t *d = (uint8_t *)destination;
		const uint8_t *s = (const uint8_t *)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

/**
 * -------------------------------------
 *  Manejo de strings.
 * -------------------------------------
 */
int strlen(char *s)
{
	int i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return i;
}
int strtok(char *s, char delim, char *array[], int arraySize)
{
	int arrayIndex = 0;
	if (*s != delim && *s != '\0')
		array[arrayIndex++] = s;
	while (*s != '\0')
	{
		if (*s == delim)
		{
			*s = 0;
			if (*(s + 1) != delim && (*(s + 1) != '\0'))
			{
				if (arrayIndex >= arraySize)
					return arrayIndex;
				array[arrayIndex++] = s + 1;
			}
		}
		s++;
	}
	return arrayIndex;
}
int strcmp(char *s1, char *s2)
{
	while (*s1 != 0 && *s2 != 0 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return *s1 == 0 && *s2 == 0;
}
// Retorna como parametro de entrada salida un string del numero ingresado.
void numToStr(int num, char *string, int len)
{
	string[len] = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		string[i] = (num % 10) + '0';
		num /= 10;
	}
}

void printInt(int num)
{
	char buffer[40];
	uintToBase(num, buffer, 10);
	print(buffer);
}

/**
 * -------------------------------------
 *  Manejo de hexa.
 * -------------------------------------
 */
uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	} while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

void printHex(uint64_t value)
{
	printBase(value, 16);
}

void printBase(uint64_t value, uint32_t base)
{
	uintToBase(value, buffer, base);
	print(buffer);
}

int pow(int base, unsigned int exp)
{
	int rta = 1;

	for (int i = 0; i < exp; i++)
		rta *= base;

	return rta;
}

uint64_t hexaToInt(char *s)
{
	int c;
	uint64_t rta = 0;

	if (*s == '0' && *(s + 1) == 'x')
		s += 2;

	int len = strlen(s);

	for (int i = 0; i < len; i++)
	{
		c = s[len - 1 - i] - '0';
		if (c < 0 || c > 9)
		{
			c = s[len - 1 - i] - 'A' + 10;
			if (c < 10 || c > 15)
				return 0;
		}
		rta += c * pow(16, i);
	}
	return rta;
}
