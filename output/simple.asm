
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
   num1 db '-'
   num1_len equ $-num1
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
   mov rax, 10
   mov rbx, 15
   add rax, rbx

   ret

; subtraction
_sub:
   mov rax, 20
   mov rbx, 10
   sub rax, rbx

   ret

; multiplication
_mul:
   mov rax, 20
   mul rax

   ret

; division
_div:
   xor   rdx, rdx   ; required to print decimal and 
   mov     rax, 400     ; move our first number into eax
   mov     rbx, 10      ; move our second number into ebx
   div     rbx         ; divide eax by ebx

   ret











;   Function exp_by_squaring_iterative(x, n)
_ipow:
   ; set the x and y values
   mov r8, 1 ; x
   mov r9, 10 ; n

   ; check if n is 1
   cmp r9, 1         ; compare n with 1
   je _equalsOne     ; goto equalsone if n is 1
   jne _notEqualsOne ; goto noequalsone if n is not 1

; return 1
_equalsOne:
   mov rax, r8 
   ret         ; if n equals 1 return x

;     if n < 0 then
_notEqualsOne:
   cmp r9, 0       ; compare n with 0
   jl _lessthan    ; goto lessthan zero if x is less than zero
   jnl _equalszero ; goto equalszero if n is equal to zero

_lessthan:
;       x := 1 / x;
;       n := -n;
   xor rdx, rdx ; zero rdx
   mov rax, 1  ; move 1 to rax
   div r8      ; divide 1 / x
   mov r8, rax ; move x back to r8
   not r9      ; revers n's bits
   
;     if n = 0 then return 1
_equalszero:   
   cmp r9, 0   ; compare n with zero
   je _ezero   ; go to ezero if n equals zero
   jne _nzero  ; go to nzero if n is not zero

_ezero: ; return 1
   mov rax, 1  ; set rax as 1 
   ret         ; return 1 if n is 0

;     y := 1;
_nzero:
   mov r10, 1 ; set r10 as 1, y

_loop1:
   mov rax, r9  ; move n to rax
   test al, 1   ; check if n is an odd number by testing the low bit 
   jz  _even    ; jump if even = lowest bit clear = zero
   jnz _odd     ; jump if odd  = lowest bit set
   
;       if n is even then 
_even:
;         x := x * x;
   mov rax, r8 ; move x to rax
   mul rax     ; multiply x by itself
   mov r8, rax ; move x back to r8

;         n := n / 2;
   mov rbx, 2  ; 2 to rbx
   mov rax, r9 ; move n to rax
   div rbx     ; divide n by 2
   mov r9, rax ; move n back

   jmp _condition ; jump over odd since if even, was processed

; n is an odd number
_odd:
;         y := x * y;
   mov rax, r10 ; move y to rax
   mul r8   ; multiply y by x
   mov r10, rax ; move y back to r10

;         x := x * x;
   mov rax, r8 ; mov x to rax
   mul rax  ; multiply x by itself 
   mov r8, rax ; mov x back to r10

;         n := (n – 1) / 2;
   mov rax, r9 ; mov n to rax
   sub rax, 1  ; minus 1 from n
   mov rbx, 2  ; set rbx as 2
   div rbx     ; divide n by 2
   mov r9, rax ; move n back to rax

;     while n > 1 do
_condition:
   cmp r9, 1   ; compare r9 with 1
   jg _loop1   ; if 1 is greater than 1 then loop

;     return x * y
   mov rax, r8 ; move x to rax
   mul r10     ; multiple x and y
   ret         ; return 











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