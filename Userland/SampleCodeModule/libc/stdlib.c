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

void printUser(){
	char s[15] = "user@TP:$ ";
	_swrite(s, 15, GREEN);
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
int strtok(char * s, char delim, char * array[], int arraySize){
	int arrayIndex = 0;
	if(*s != delim && *s != '\0')
		array[arrayIndex++] = s;
	while( *s != '\0' ){
		if(*s == delim){
			*s = 0;
			if( *(s+1) != delim &&  (*(s+1) != '\0')){
				if(arrayIndex >= arraySize)
					return arrayIndex;
				array[arrayIndex++] = s + 1;
			}
		}
		s++;
	}
	return arrayIndex;
} 
int strcmp(char * s1, char * s2){
	while(*s1 != 0 && *s2 != 0 && *s1 == *s2){
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

int pow(int base, unsigned int exp){
	int rta = 1;

	for (int i = 0; i < exp; i++)
		rta *= base;

	return rta;
	
}

uint64_t hexaToInt(char * s){
	int c;
	uint64_t rta = 0;
	
	if(*s == '0' && *(s+1) == 'x')
		s += 2;

	int len = strlen(s);
	
	for (int i = 0; i < len; i++){
		c = s[len - 1 - i] - '0';
		if(c < 0 || c > 9){
			c = s[len - 1 - i] - 'A' + 10;
			if(c < 10 || c > 15)
				return 0;
		}
		rta += c*pow(16, i);
	}
	return rta;
}

// void hexaToInt(uint64_t value){
//     int buffer[16];
//     int dig = unitToBase(value, buffer, 16);
//     int num = 16 - dig; 
//     for(int i=15; i >= 0; i--){
//         if(i >= num){
//                 buffer[i] = buffer[i-num];
//             }else{
//                 buffer[i] = '0';
//             }
//     }
// }
