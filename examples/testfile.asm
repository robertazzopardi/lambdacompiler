%include 'lib/functions.asm'

global main
extern printf

section .data
	sum1 DQ 0
	integerfmt db '%d', 10, 0
	floatfmt db '%.6g', 10, 0

section .text

main:
	_div 1, 3, [sum1]
	print_float [sum1], floatfmt

	ret