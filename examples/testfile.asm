%include 'lib/functions.asm'

global main
extern printf

section .data
	sum DQ 0
	integerfmt db '%d', 10, 0

section .text

main:
	_add 2, 3, qword [sum]
	_add 1, 2, qword [sum]
	_add 100, 100, qword [sum]
	print_sum qword [sum], integerfmt
	print_sum qword [sum], integerfmt
	print_sum qword [sum], integerfmt

	ret