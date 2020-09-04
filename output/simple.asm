
; section .data
   ; num1 db '-'
   ; num1_len equ $-num1

   ; message db "Hello, world!", nl
   ; message_len equ $-message

; section .text

; global _start
; _start:
;    ; write to console
;    mov rax, sys_write
;    mov rdi, stdout

;    mov rsi, message
;    mov rdx, message_len

;    syscall ; call kernal interrupt

;    mov rax, sys_exit ; set exit command
;    mov rdi, success ; set return code
;    syscall ; call kernal interrupt

%include 'functions.asm'

section .bss
	digitSpace resb 100
	digitSpacePos resb 8

section .data
   negsign db '-'
   negsign_len equ $-negsign
	; text db "Hello, World!",10,0




section .text
	global _start

_start:

   ; operation
	; mov rax, 257
   ; ; add rax, 100
   ; mov rcx, 10000
   ; mul rcx

   ; mov rax, 10
   ; sub rax, 10
   call _add
	call _printRAX


   call _sub
   call _printRAX


   call _mul
   call _printRAX


   call _div
   call _printRAX




   call _ipow
   call _printRAX



   ; exit
   call _exit

; addition
_add:
   mov rax, 10000
   mov rbx, 15
   add rax, rbx

   ret

; subtraction
_sub:
   mov rax, 200
   mov rbx, 10
   sub rax, rbx

   ret

; multiplication
_mul:
   mov rax, 20
   mov rbx, 33
   mul rbx

   ret

; division
_div:
   xor   rdx, rdx   ; required to print decimal and
   mov     rax, 400     ; move our first number into eax
   mov     rbx, 10      ; move our second number into ebx
   div     rbx         ; divide eax by ebx

   ret











; power
_ipow:
   mov r8, 2 ; x
   mov r9, 3 ; n

   ; check if n is 1
   cmp r9, 1         ; compare n with 1
   jne _notEqualsOne ; goto noequalsone if n is not 1

   mov rax, r8  ; return 1
   ret         ; if n equals 1 return x

_notEqualsOne:
   test r9, r9       ;     if n < 0
   jnl _equalszero ; goto equalszero if n is equal to zero

   xor rdx, rdx ; zero rdx
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
   test al, 1   ; check if n is an odd number by testing the low bit
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











;   Function exp_by_squaring_iterative(x, n)
;     if n < 0 then
;       x := 1 / x;
;       n := -n;

;     if n = 0 then return 1

;     y := 1;

;     while n > 1 do
;       if n is even then
;         x := x * x;
;         n := n / 2;
;       else
;         y := x * y;
;         x := x * x;
;         n := (n – 1) / 2;
;     return x * y