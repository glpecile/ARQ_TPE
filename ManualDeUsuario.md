## Autores
<hr>

- [Roberto José Catalán](https://github.com/rcatalan98)

- [Desiree Melisa Limachi](https://github.com/dlimachi)
 
- [Gian Luca Pecile](https://github.com/glpecile)

<hr>

# Manual de Usuario
Sistema operativo básico basado en Barebonesx64 por RowDaBoat. Para poder correr el sistema se debe tener instalado qemu-system a fin de visualizar y docker instalado para el compilado con el contenedor `agodio/itba-so:1.0` dado por la cátedra. Al tener dichos requisitos se debe compilar desde docker y luego ejecutar usando:
1. La primera vez que se accede ```cd Toolchain``` y luego ```make all```. Este paso solo se debe realizar la primera vez que se descarga el repositorio.
2. Ahora resta una úntima compilación del proyecto volviendo al directorio anterior y utilizando ```make all```.
3. Por último resta correr el sistema utilizando qemu con el comando ```run.sh```.

## Shell
Intéprete de comandos del usuario, el sistema inicia al mismo por defecto. 
Dispone de las siguientes funcionalidades:
- **help**: Despliega en pantalla las funciones disponibles para el usuario. 
- **inforeg**: Despliega en pantalla un snapshot de los registros al momento que es llamado.
- **printmem**: Despliega en pantalla un volcado de memoria de 32 bytes a partir de una dirección de memoria válida recibida como argumento.
- **time**: Despliega en pantalla información sobre el día y hora actual del sistema.
- **invalidOpCodeException**: Verifica el funcionamiento correcto de la excepción de tipo operación de código inválido.
- **invalidZeroDivisionException**: Verifica el funcionamiento correcto de la excepción de tipo división por cero.
- **chess**: Despliega juego de ajedrez en formato gráfico humano a humano. Al escribir ```chess -man``` se despliega un menú con las reglas del juego. Además, se dispone de una opción para continuar una partida existente usando ```chess -c```. 
- **clear**: Limpia la pantalla de los comandos ingresados.

## Chess
¡Juegue una nueva partida o reanude su partida existente de ajedrez en formato gráfico por comando de línea! 
- Aplica toda regla general documentada del ajedrez. Se puede ganar el juego al realizar un haque mate o bien al comer al rey.
- En la parte inferior de la pantalla, centrado se encuentra un contador por turno donde el jugador no puede tener de diferencia de tiempo mayor a un minuto con respecto al tiempo que tomó la jugada del juador anterior. En caso de ser el primer moviemiento de la partida no puede superar un minuto el mismo. Si se supera dicho tiempo automáticamente gana la partida el jugador contrario.
- Para poder realizar un movimiento primero debe tener el formato ```'FROM_X''FROM_Y' 'TO_X''TO_Y'``` con **toda letra ingresada para un movimiento en mayúscula** debido a la existencia de caracteres especiales reservados:
  - Coronación: Todo peón es coronado a una reína por defecto.
  - Enroque: Para realizar un enroque corto ```e 2``` mientras que un enroque largo se realiza con ```e 3```.
  - Rotación: ```r``` para rotar 90° la posición de las piezas y tablero de ajedrez.
  - Salida: ```Esc``` la tecla de escape permite salir del juego con la habilidad de resumir la partida ingresando ```chess -c``` desde la terminal.
- Luego de realizar una jugada válida, la misma se imprimirá en pantalla, a modo de log, como jugada exitosa y luego se cambiara de turno reiniciando el contador. Se puede recrear la partida si se lo desea con las jugadas existentes del log.

## Syscalls

***int 80h***

| %rdi | System Call           | %rsi              | %rdx              | %rcx              | %r8                 | %r9    |
| ---- | --------------------  | ----------------- | ----------------- | ----------------- | ------------------- | -----  |
| 0    | void timerFunc        | void (*f)         | int toDo          |                   |                     |        |
| 1    | uint8_t getTime       | int descriptor    |                   |                   |                     |        |
| 2    | void drawFigure       | char *toDraw      | int color         | int size          | int x               |        |
| 3    | uint64_t sWrite       | char * string     | uint8_t length    | t_colour bgColour | t_colour fontColour | int y  |
| 4    | char sGetChar         |                   |                   |                   |                     |        |
| 5    | void setCursor        | unsigned int x    | unsigned int y    | int color         |                     |        |
| 6    | void clearScreen      |                   |                   |                   |                     |        |
| 7    | void getPixelWidth()  |                   |                   |                   |                     |        |
| 8    | void getPixelWidth()  |                   |                   |                   |                     |        |
