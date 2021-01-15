%include 'lib/functions.asm'

global _main
extern _printf


default rel

section .data

	integerfmt db '%d', 10, 0
	floatfmt db '%.6g', 10, 0

section .text

_main:

	mov			rax,	1
	mov			rbx,	2
	add			rax,	rbx
	mov			rcx,	rax
	mov			rbx,	3
	add			rax,	rbx
	mov			rbx,	4
	add			rax,	rbx
	mov			rbx,	10
	sub			rax,	rbx
	mov			rsi,	rcx
	sub			rsp,	8
	lea			rdi,	integerfmt
	xor			rax,	rax
	call		_printf
	add			rsp,	8
	xor			rdi,	rdi

	ret
