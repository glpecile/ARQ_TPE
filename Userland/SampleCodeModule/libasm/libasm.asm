;
; libasm.asm: liberia assembler para usuario.
;
GLOBAL getRegs
EXTERN inforeg

section .text 

;
; Funcion para obtener los valores de todos los registros y asi poder imprimirlos (inforeg)
;
getRegs:
    mov [regMem], rax
    mov [regMem + 1*8], rbx
    mov [regMem + 2*8], rcx
    mov [regMem + 3*8], rdx
    mov [regMem + 4*8], rbp
    mov [regMem + 5*8], rdi
    mov [regMem + 6*8], rsi
    mov [regMem + 7*8], r8
    mov [regMem + 8*8], r9
    mov [regMem + 9*8], r10
    mov [regMem + 10*8], r11
    mov [regMem + 11*8], r12
    mov [regMem + 12*8], r13
    mov [regMem + 13*8], r14
    mov [regMem + 14*8], r15
	mov rax, [rsp] ; RIP.
    mov [regMem + 15*8], rax
    add rsp, 8
	mov [regMem + 16*8], rsp ; Valore previo rsp.
    sub rsp, 8

    mov rdi, regMem
	call inforeg

    ret

section .bss
regMem: resb 17*8