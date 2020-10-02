%include '../lib/functions.asm'

global _main
extern _printf


default rel

section .data
	sum1 DQ 0
	sum2 DQ 0
	sum3 DQ 0
	sum4 DQ 0

	integerfmt db '%d', 10, 0
	floatfmt db '%.6g', 10, 0

section .text

_main:

	_add 1, 2, [sum1]
	mov rsi, [rel sum1]
	lea rdi, integerfmt
	xor rax,            rax
	call _printf
	xor rdi,            rdi

	_div 1, 3, [sum2]
	movq xmm0, [rel sum2]
	sub rsp, 8
	lea rdi, floatfmt
	mov rax, 1
	call _printf
	add rsp, 8
	xor eax, eax
	xor edi, edi

	_add 1, 2, [sum3]
	mov rsi, [rel sum3]
	lea rdi, integerfmt
	xor rax,            rax
	call _printf
	xor rdi,            rdi

	; _mod 7, 8, [sum4]
	; mov r8, 2
	; mov r9, [sum4]
 	; call _ipow
	; mov [sum4], rax
	; mov rsi, [rel sum4]
	; lea rdi, integerfmt
	; xor rax,            rax
	; call _printf
	; xor rdi,            rdi

	ret
