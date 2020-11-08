;
; syscallManager.asm: Manejo de syscalls de Userland a Kernerl.
; Si bien se debe reducir el código en assembler por no ser portable,
; es indispensable para la conexión por la interrupción int80h (igual que Linux).
GLOBAL _getTime
GLOBAL _sGetChar
GLOBAL _swrite
GLOBAL _setCursor
GLOBAL _drawFigure
GLOBAL _clearScreen
GLOBAL _timerFunc
GLOBAL _getPixelHeight
GLOBAL _getPixelWidth

SECTION .text


%macro pushState 0
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
%endmacro

%macro syscall 1
	pushState
	mov	r10, r9 ; sexto. Se pasa otro vector en drawFigure.
	mov	r9, r8 ; quinto. Se pasa un vector en drawFigure.
	mov r8, rcx  ; cuarto.
    mov rcx, rdx ; tercero.
	mov rdx, rsi ; segundo.
	mov rsi, rdi ; primer parametro que reciben las funciones.
	mov rdi, %1 ; pasaje de parametro de syscall.	
    int 80h ; interrupción.

	popState
    ret     
%endmacro

_timerFunc:
	syscall 0
_getTime:
    syscall 1
_drawFigure:
	syscall 2
_swrite:
	syscall 3
_sGetChar:
    syscall 4
_setCursor:
	syscall 5
_clearScreen:
	syscall 6
_getPixelHeight:
	syscall 7
_getPixelWidth:
	syscall 8