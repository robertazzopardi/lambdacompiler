%include 'lib/functions.asm'

global main
extern printf

section .data
	sum DQ 0
	integerfmt db '%d', 10, 0

section .text

main:
	_add 2, 3, qword [sum]
	print_sum [sum], integerfmt

	_add 2, 30, qword [sum]
	print_sum [sum], integerfmt

	_add 1, 2, qword [sum]
	print_sum [sum], integerfmt

	_add 100, 100, qword [sum]
	print_sum [sum], integerfmt

	_add 5, 5, qword [sum]
	print_sum [sum], integerfmt

	mov r8, 8
	mov r9, 2
	call _ipow
	mov [sum], rax
	print_sum [sum], integerfmt


	ret