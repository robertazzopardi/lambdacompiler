; nasm -felf64 hola.asm && gcc -no-pie hola.o && ./a.out
; needed things 
;   wrt ..plt
;   gcc -no-pie

; nasm -felf64 hola.asm && ld hola.o && ./a.out


%include 'functions.asm'


section .bss
	digitSpace 		  resb 100
	digitSpacePos 	resb 8


section .data
	negsign 		    db '-'
	negsign_len 	  equ $-negsign

  choice	    	  DB	'y'
  number		      DW	12345
  neg_number	    DW	-12345
  big_number	    DQ	123456789
  real_number1	  DD	1.234
  real_number2	  DQ	123.456

section .text
	global _start

_start:
  mov rax, number
  call _print

  call _exit

