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
	mov			rbx,	3
	cvtsi2sd	xmm0,	rax
	cvtsi2sd	xmm1,	rbx
	divsd		xmm0,	xmm1
	mov			rax,	1
	cvtsi2sd	xmm1,	rax
	addsd		xmm0,	xmm1
	movq		rcx,	xmm0
	movq		xmm0,	rcx
	sub			rsp,	8
	lea			rdi,	floatfmt
	mov			rax,	1
	call		_printf
	add			rsp,	8
	xor			eax,	eax
	xor			edi,	edi

	mov			rax,	1
	mov			rbx,	3
	cvtsi2sd	xmm0,	rax
	cvtsi2sd	xmm1,	rbx
	divsd		xmm0,	xmm1
	mov			rax,	1
	cvtsi2sd	xmm1,	rax
	subsd		xmm0,	xmm1
	movq		rcx,	xmm0
	movq		xmm0,	rcx
	sub			rsp,	8
	lea			rdi,	floatfmt
	mov			rax,	1
	call		_printf
	add			rsp,	8
	xor			eax,	eax
	xor			edi,	edi

	mov			rax,	1
	mov			rbx,	2
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	3
	add			rax,	rbx
	mov			rcx,	rax
	mov			rsi,	rcx
	sub			rsp,	8
	lea			rdi,	integerfmt
	xor			rax,	rax
	call		_printf
	add			rsp,	8
	xor			rdi,	rdi

	ret
