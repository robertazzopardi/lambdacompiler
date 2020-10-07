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

	mov			rax,	1
	mov			rbx,	2
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	3
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	4
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	10
	sub			rax,	rbx
	mov			rcx,	rax
	mov			rsi,	rcx
	sub			rsp,	8
	lea			rdi,	integerfmt
	xor			rax,	rax
	call		_printf
	add			rsp,	8
	xor			rdi,	rdi

	mov			rax,	400
	mov			rbx,	20
	cvtsi2sd	xmm0,	rax
	cvtsi2sd	xmm1,	rbx
	divsd		xmm0,	xmm1
	sub			rsp,	8
	lea			rdi,	floatfmt
	mov			rax,	1
	call		_printf
	add			rsp,	8
	xor			eax,	eax
	xor			edi,	edi

	mov			rax,	3
	mov			rbx,	2
	mov			r8,	rax
	mov			r9,	rbx
	call		_ipow
	mov			rcx,	rax
	mov			rsi,	rcx
	sub			rsp,	8
	lea			rdi,	integerfmt
	xor			rax,	rax
	call		_printf
	add			rsp,	8
	xor			rdi,	rdi

	mov			rax,	0
	mov			rbx,	1
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	2
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	3
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	4
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	5
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	6
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	7
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	8
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	9
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	10
	add			rax,	rbx
	mov			rcx,	rax
	mov			rsi,	rcx
	sub			rsp,	8
	lea			rdi,	integerfmt
	xor			rax,	rax
	call		_printf
	add			rsp,	8
	xor			rdi,	rdi

	mov			rax,	1
	mov			rbx,	2
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	2
	mov			rbx,	2
	add			rax,	rbx
	sub			rcx,	rax
	mov			rsi,	rcx
	sub			rsp,	8
	lea			rdi,	integerfmt
	xor			rax,	rax
	call		_printf
	add			rsp,	8
	xor			rdi,	rdi

	mov			rax,	3
	mov			rbx,	1
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	2
	mov			rbx,	3
	add			rax,	rbx
	add			rcx,	rax
	mov			rax,	3
	mov			rbx,	4
	add			rax,	rbx
	add			rcx,	rax
	mov			rsi,	rcx
	sub			rsp,	8
	lea			rdi,	integerfmt
	xor			rax,	rax
	call		_printf
	add			rsp,	8
	xor			rdi,	rdi

	mov			rax,	90
	mov			rbx,	7
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	8
	cvtsi2sd	xmm1,	rax
	divsd		xmm0,	xmm1
	movq		rcx,	xmm0
	mov			rbx,	1
	cvtsi2sd		xmm1,	rbx
	addsd		xmm0,	xmm1
	movq			rcx,	xmm0
	mov			rax,	10
	cvtsi2sd	xmm1,	rax
	subsd		xmm0,	xmm1
	movq		rcx,	xmm0
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
	divsd		xmm0,	xmm1
	movq		rcx,	xmm0
	sub			rsp,	8
	lea			rdi,	floatfmt
	mov			rax,	1
	call		_printf
	add			rsp,	8
	xor			eax,	eax
	xor			edi,	edi

	mov			rax,	90
	mov			rbx,	7
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	8
	mul			rbx
	mov			rcx,	rax
	mov			rax,	1
	mov			rbx,	rcx
	add			rax,	rbx
	mov			rcx,	rax
	mov			rax,	rcx
	mov			rbx,	10
	sub			rax,	rbx
	mov			rcx,	rax
	mov			rsi,	rcx
	sub			rsp,	8
	lea			rdi,	integerfmt
	xor			rax,	rax
	call		_printf
	add			rsp,	8
	xor			rdi,	rdi

	mov			rax,	2
	mov			rbx,	2
	mov			r8,	rax
	mov			r9,	rbx
	call		_ipow
	mov			rcx,	rax
	mov			rax,	2
	mov			rbx,	rcx
	mov			r8,	rax
	mov			r9,	rbx
	call		_ipow
	mov			rcx,	rax
	mov			rsi,	rcx
	sub			rsp,	8
	lea			rdi,	integerfmt
	xor			rax,	rax
	call		_printf
	add			rsp,	8
	xor			rdi,	rdi

	ret
