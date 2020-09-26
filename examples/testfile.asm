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
	sum11 DQ 0
	sum12 DQ 0
	sum13 DQ 0
	sum14 DQ 0
	sum15 DQ 0
	integerfmt db '%d', 10, 0
	floatfmt db  '%.6g', 10, 0

section .text

main:
	_mul 3, 3, [sum1]
	_mul [sum1], 3, [sum2]
	print_sum [sum2], integerfmt

	_mul 2, 2, [sum3]
	_mul [sum3], 2, [sum4]
	_mul [sum4], 2, [sum5]
	print_sum [sum5], integerfmt

	_add 3, 1, [sum6]
	_add 2, 3, [sum7]
	_add [sum7], [sum6], [sum7]
	_add 3, 4, [sum8]
	_add [sum8], [sum7], [sum8]
	print_sum [sum8], integerfmt

	_mul 1, 8, [sum9]
	mov r8, 3
	mov r9, 7
	call _ipow
	mov [sum10], rax
	_add [sum10], [sum9], [sum10]
	print_sum [sum10], integerfmt

	mov r8, 2
	mov r9, 1
	call _ipow
	mov [sum11], rax
	mov r8, 4
	mov r9, [sum11]
 	call _ipow
	mov [sum11], rax
	mov r8, 3
	mov r9, [sum11]
 	call _ipow
	mov [sum11], rax
	print_sum [sum11], integerfmt

	_mul 4, 2, [sum12]
	_sub 1, 5, [sum13]
	mov r8, 2
	mov r9, 3
	call _ipow
	mov [sum14], rax
	mov r8, [sum13]
	mov r9, [sum14]
 	call _ipow
	_div [sum14], rax, [sum14]
	_div [sum14], [sum13], [sum14]
	_add [sum15], 3, [sum15]
	print_sum [sum15], integerfmt

	ret