/**
 * stdlib.c: Libería estandar del usuario.
 */
#include <stdlib.h>

int getChar()
{
    char c = 0;
    // sread(1, &c, 1); // 1: leyo del teclado, &c:el buffer, 1:la cant de ingreso, lea de un char
    return c;
}

void putChar(char c)
{
    _swrite(&c, 1); // Recibe de a una letra, su long es 1 siempre
}

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

void print(char *s)
{
    int lenght = strlen(s); // Buscamos el largo.
    _swrite(s, lenght);
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