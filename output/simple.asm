
; section .data
;    num1 db '3'
;    num1_len equ $-num1

;    message db "Hello, world!", nl
;    message_len equ $-message

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


   ; call _logicaland
   ; call _printRAX
   



   call _pow
   call _printRAX



   ; exit 
   call _exit

_add:
   mov rax, 10
   mov rbx, 15
   add rax, rbx

   ret

_sub:
   mov rax, 20
   mov rbx, 10
   sub rax, rbx

   ret

_mul:
   mov rax, 20
   mul rax

   ret

_div:
   xor   rdx, rdx   ; required to print decimal and 
   mov     rax, 400     ; move our first number into eax
   mov     rbx, 10      ; move our second number into ebx
   div     rbx         ; divide eax by ebx

   ret

; _logicaland:;&
;    mov rax, 4
;    mov rbx, 6
;    and rax, rbx

;    ret


; 2 ^ 4 = 16
; x   n  
_pow: 
;   Function exp_by_squaring_iterative(x, n)
   mov r8, 9 ; x
   mov r9, 9 ; n
   
   ; if n less than 0
   cmp r9, 0
   jl _lessthan
   jnl _nolessthan

_lessthan:
   mov rax, 9900090999 ; change later
   jmp _equalszero

_nolessthan:
   

_equalszero:
   cmp r9, 0
   je _ezero
   jne _nzero

_ezero:
   mov rax, 1
   ret

_nzero:
   mov r10, 1 ; y

_loop1:
   mov rax, r9
   test al, 1
   jz  _even    ; jump if even = lowest bit clear = zero
   jnz _odd    ; jump if odd  = lowest bit set
   
   _even:
      xor rdx, rdx
      mov rax, r8
      mul rax
      mov r8, rax

      mov rbx, 2
      mov rax, r9
      div rbx
      mov r9, rax

      jmp _condition

   _odd:
      xor rdx, rdx

      mov rax, r10
      mul r8
      mov r10, rax

      mov rax, r8
      mul rax
      mov r8, rax

      mov rax, r9
      sub rax, 1
      mov rbx, 2
      div rbx
      mov r9, rax


_condition:
   cmp r9, 1
   jg _loop1
   jle _leone

_leone:
mov rax, r8
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