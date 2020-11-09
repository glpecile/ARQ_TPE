## Autores
<hr>

- [Roberto José Catalán](https://github.com/rcatalan98)

- [Desiree Melisa Limachi](https://github.com/dlimachi)
 
- [Gian Luca Pecile](https://github.com/glpecile)

<hr>

## Syscalls

***int 80h***

| %rdi | System Call   | %rsi             | %rdx              | %r10              | %r8                 | %r7 | %r6 |
| ---- | -----------   | ---------------- | ----------------- | ----------------- | ------------------- | --- | --- |
| 0    | sTicksElapsed |                  |                   |                   |                     |     |     |
| 1    | sGetTime      | int descriptor   |                   |                   |                     |     |     |
| 2    | sRead         |                  |                   |                   |                     |     |     |
| 3    | sWrite        | char * string    | uint8_t length    | t_colour bgColour | t_colour fontColour |     |     |
| 4    | sGetChar      |                  |                   |                   |                     |     |     |
| 5    | sGetRegisters |                  |                   |                   |                     |     |     |

