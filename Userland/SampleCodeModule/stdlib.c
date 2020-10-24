#ifndef __STDINT_H_
#define __STDINT_H_
#include <stdint.h>
#endif

#ifndef __STDLIB_H_
#define __STDLIB_H_
#include <stdlib.h>
#endif

extern int swrite(char *buffer, int size);
extern int sread(unsigned int fd, const char *buffer, int size);

int getChar(){
    char c = 0;
    sread(1, &c, 1); // 1: leyo del teclado, &c:el buffer, 1:la cant de ingreso, lea de un char 
    return c;
}

void printChar(char c){
    swrite(&c, 1); //recibe de a una letra, su long es 1 siempre
}

int strlen(char *s){
    int i = 0;
    while(*s != '\0'){
        i++;
        s++;
    }
    return i;
}

void print(char *s){
    int lenght = strlen(s); // buscamos el largo.
    swrite(s, lenght); 
}

int scan(char *buffer, int size){
    char c = 0;
    int len = 0;
    while((c=getChar()) != '\n' && len < size){
        printChar(c);
        buffer[len] = c;
        len++;
    }
    buffer[len] = '\0';
    return len;
}

