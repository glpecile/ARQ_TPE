GLOBAL keyboardActivated
GLOBAL getKeyboardScancode

section .text
; -----------------------------------
; Detecta si hay un codigo de teclado en el buffer.
; Retorna 1 de haber, 0 si no.
; -----------------------------------
keyboardActivated:
    mov rax, 0
    in al, 64h
    and al, 01h 
    ret
; -----------------------------------
; Devuelve el codigo de teclado del buffer.
; Retorna el codigo del teclado.
; -----------------------------------
getKeyboardScancode:
    mov rax, 0
    in al, 60h
    ret