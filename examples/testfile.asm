%include 'lib/functions.asm'

global main
extern printf

section .data
	sum DQ 0
	integerfmt db '%d', 10, 0

section .text

main:
	_add 1, 102, qword [sum]
	print_sum qword [sum], integerfmt

	ret