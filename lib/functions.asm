%define sys_write 1
%define stdout 1

%define sys_exit 60
%define success 0

%define ascii_off 48
%define nl 10

; ------------------------------------------------------------------------------
; EXIT PROGRAM
_exit:
  mov        rax, sys_exit
  mov        rdi, success
  syscall

; ADD INTEGERS
%macro _add 3
  mov        rax,            %1
  mov        rbx,            %2
  add        rax,            rbx
  mov        %3,             rax
  mov        rax,            0
%endmacro

; ADD FLOATS


; SUB INTEGERS
%macro _sub 3
  mov        rax, %1
  mov        rbx, %2
  sub        rax, rbx
  mov        %3, rax
  mov        rax, 0
%endmacro

; MULTIPLY INTEGERS
%macro _mul 3
  mov        rax, %1
  mov        rbx, %2
  mul        rbx
  mov        %3, rax
  mov        rax, 0
%endmacro

; DIVIDE INTEGERS
%macro _div 3
  mov        rax, %1
  mov        rbx, %2
  movq       xmm0, rax              ; load from memory
  movq       xmm1, rbx
  divsd      xmm0, xmm1             ; need to be same type
  movq       %3, xmm0
%endmacro

; PRINT INTEGERS
; %macro print_sum 2
;     mov rsi,            %1
;     mov rdi,            %2
;     xor rax,            rax
;     call _printf
;     xor rdi,            rdi
; %endmacro

; ; PRINT FLOATS
; %macro print_float 2
;     movq xmm0, %1

;     sub rsp, 8 ; align stack for print_float
;     lea rdi, %2
;     mov rax, 1
;     call _printf
;     add rsp, 8 ; Clean up stack

;     xor eax, eax
;     xor edi, edi
; %endmacro

; FIND THE REMAINDER
%macro _mod 3
  xor        edx, edx               ; required to print decimal and
  mov        rax, %1                ; move our first number into eax
  mov        rbx, %2                ; move our second number into ebx
  div        rbx                    ; divide eax by ebx

  mov        %3, rdx
%endmacro

; FIND X TO POWER N
_ipow:
;    mov r8, 2 ; x
;    mov r9, 15 ; n

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