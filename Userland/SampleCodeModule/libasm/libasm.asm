GLOBAL swrite
GLOBAL sread
GLOBAL exit

section .text 

; int swrite(unsigned int fd, char *buffer, int size, int color);
swrite:
    enter 0,0

    mov rax, 1      ;syscall de write.
    syscall

    leave
    ret 

; int sread(unsigned int fd, const char *buffer, int size);
sread:
    enter 0,0

    mov rax, 0      ;syscall de read
    syscall

    leave
    ret

; void exit(int return_value);
exit:
	push rbp
	mov rbp, rsp

	mov rax, 0x3c
	syscall

	mov rsp, rbp
	pop rbp
	ret