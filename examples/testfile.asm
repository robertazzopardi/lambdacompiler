%include 'lib/functions.asm'

global main
extern printf

section .data
	sum1 DQ 0
	sum2 DQ 0
	sum3 DQ 0
	sum4 DQ 0
	integerfmt db '%d', 10, 0
	floatfmt db '%.6g', 10, 0

section .text

main:
	mov r8, 67
	mov r9, 2
	call _ipow
	mov [sum1], rax
	_mod 9999, [sum1], [sum2]
	print_sum [sum2], integerfmt

	_div 1, 3, [sum3]
	print_float [sum3], floatfmt

	_mod 7, 8, [sum4]
	mov r8, 2
	mov r9, [sum4]
 	call _ipow
	mov [sum4], rax
	print_sum [sum4], integerfmt

	ret