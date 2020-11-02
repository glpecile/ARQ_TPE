GLOBAL cpuVendor
GLOBAL getRTC
GLOBAL getSP
section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

getRTC:
	mov rax, rdi	; recibimos por parámetro.
	out 70h, al		; 70h entrada para la informacion que quiero en 71h.
	mov rax, 0		
	in al, 71h		; en al se deposita lo pedido por 70h, presente en 71h.
	ret
getSP:
	mov rax, rsp
	ret