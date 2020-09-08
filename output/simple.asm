;  nasm -felf64 simple.asm && ld simple.o && ./a.out

%include 'functions.asm'


section .bss
	digitSpace 		resb 100
	digitSpacePos 	resb 8


section .data
	negsign 		db '-'
	negsign_len 	equ $-negsign
	; text db "Hello, World!",10,0


section .text
	global _start


_start:

; testing -------------------------

; ---------------------------------


;----------------------------------
	call _add
	call _print
;----------------------------------

;----------------------------------
	call _sub
	call _print
;----------------------------------

;----------------------------------
	call _mul
	call _print
;----------------------------------

;----------------------------------
	call _div
	call _print
;----------------------------------

;----------------------------------
	call _ipow
	call _print
;----------------------------------

   ; exit
	call _exit



; addition ---------------------------------------------------------
_add:
	mov rax, 10 ;convert char to int (or something)
	mov rbx, 10
	add rax, rbx

	ret
; ------------------------------------------------------------------

; subtraction ------------------------------------------------------
_sub:
	mov rax, 5
	mov rbx, 100
	sub rax, rbx

	ret
; ------------------------------------------------------------------

; multiplication ---------------------------------------------------
_mul:
	mov rax, -20
	mov rbx, 33
	mul rbx

	ret
; ------------------------------------------------------------------

; division ---------------------------------------------------------
_div:
	xor   edx, edx   ; required to print decimal and
	mov     rax, 400     ; move our first number into eax
	mov     rbx, 10      ; move our second number into ebx
	div     rbx         ; divide eax by ebx

	ret
; ------------------------------------------------------------------

; power ------------------------------------------------------------
_ipow:
   mov r8, 2 ; x
   mov r9, 15 ; n

   ; check if n is 1
   cmp r9, 1         ; compare n with 1
   jne _notEqualsOne ; goto noequalsone if n is not 1

   mov rax, r8  ; return 1 which should be 1
   ret         ; if n equals 1 return x

_notEqualsOne:
   test r9, r9       ;     if n < 0
   jnl _equalszero ; goto equalszero if n is equal to zero

   xor edx, edx ; zero rdx
   mov eax, 1
   div r8      ; x := 1 / x;
   mov r8, rax
   not r9   ; n := -n;

_equalszero:
   jne _nzero  ; n != 0

   mov eax, 1  ; return 1
   ret         ; return 1 if n is 0

_nzero:
   mov r10, 1 ; y := 1;

_loop1:
   mov rax, r9
   test al, 1   ; check if n is an odd number
   jz _even    ; n is even

   ; n is odd
   imul r10, r8 ; y := x * y;
   sub r9, 1 ; n - 1

_even: ; n is 0
   imul r8, r8 ; x := x * x;
   shr r9, 1 ; n / 2

   cmp r9, 1   ; while n > 1 do
   jg _loop1   ; if 1 is greater than 1 then loop

   mov rax, r8 ; return x * y
   mul r10
   ret
; ------------------------------------------------------------------