## Autores
<hr>

- [Roberto José Catalán](https://github.com/rcatalan98)

- [Desiree Melisa Limachi](https://github.com/dlimachi)
 
- [Gian Luca Pecile](https://github.com/glpecile)

<hr>

# Manual de Usuario

## Shell
Intéprete de comandos del usuario, es lo primero con lo que inicia el sistema. 
Dispone de las siguientes funcionalidades:
- **help**: Despliega en pantalla las funciones disponibles para el usuario. 
- **inforeg**: Despliega en pantalla un snapshot de los registros al momento que es llamado.
- **printmem**: Despliega en pantalla un volcado de memoria de 32 bytes a partir de una dirección de memoria válida recibida como argumento.
- **time**: Despliega en pantalla información sobre el día y hora actual del sistema.
- **invalidOpCodeException**: Verifica el funcionamiento correcto de la excepción de tipo operación de código inválido.
- **invalidZeroDivisionException**: Verifica el funcionamiento correcto de la excepción de tipo división por cero.
- **chess**: Despliega juego de ajedrez en formato gráfico humano a humano.
- **clear**: Limpia la pantalla de los comandos ingreados.

## Chess

## Syscalls

***int 80h***

| %rdi | System Call   | %rsi              | %rdx              | %rcx              | %r8                 | %r9    |
| ---- | -----------   | ----------------- | ----------------- | ----------------- | ------------------- | -----  |
| 0    | timerFunc     | void (*f)         | int toDo          |                   |                     |        |
| 1    | getTime       | int descriptor    |                   |                   |                     |        |
| 2    | drawFigure    | char *toDraw      | int color         | int size          | int x               |        |
| 3    | sWrite        | char * string     | uint8_t length    | t_colour bgColour | t_colour fontColour | int y  |
| 4    | sGetChar      |                   |                   |                   |                     |        |
| 5    | setCursor     | unsigned int x    | unsigned int y    |                   |                     |        |
| 6    | clearScreen   |                   |                   |                   |                     |        |
