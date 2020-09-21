%include 'lib/functions.asm'

global main
extern printf

section .data
	sum DQ 0
	integerfmt db '%d', 10, 0

section .text

main:
	_add 2, 3, [sum]
	print_sum [sum], integerfmt

	_add 2, 2, [sum]
	_sub [sum], 2, [sum]
	mov r8, 33
	mov r9, 4
	call _ipow
	sub [sum], rax
	print_sum [sum], integerfmt

	_add 3, 1, [sum]
	_add 2, 3, [sum]
	_add 3, 4, [sum]
	print_sum [sum], integerfmt


	ret