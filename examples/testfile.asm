%include 'lib/functions.asm'

global main
extern printf

section .data
	sum1 DQ 0
	sum2 DQ 0
	sum3 DQ 0
	sum4 DQ 0
	sum5 DQ 0
	sum6 DQ 0
	sum7 DQ 0
	sum8 DQ 0
	sum9 DQ 0
	sum10 DQ 0

	integerfmt db '%d', 10, 0

section .text

main:
	mov r8, 3
	mov r9, 3
	call _ipow
	mov [sum1], rax
	mov r8, [sum1]
	mov r9, 3
	call _ipow
	mov [sum2], rax
	print_sum [sum2], integerfmt

	_mul 3, 3, [sum3]
	_mul [sum3], 3, [sum4]
	print_sum [sum4], integerfmt

	_mul 2, 2, [sum5]
	_mul [sum5], 2, [sum6]
	_mul [sum6], 2, [sum7]
	print_sum [sum7], integerfmt

	_add 3, 1, [sum8]
	_add 2, 3, [sum9]
	_add 3, 4, [sum10]
	print_sum [sum10], integerfmt

	ret