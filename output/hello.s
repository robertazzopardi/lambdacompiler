; nasm hello.s -f elf64 -o hello.o && gcc -no-pie -Wall -Wextra -Werror -o hello hello.o && ./hello

; section .rodata
;     format: db 'Hello %s', 10, 0
;     name:   db 'Conrad', 0

;     numberfmt: db '%f', 10, 0
;     number: dq 1.233

; section .text
;         global main
;         extern printf

;     main:
;         mov rdi, numberfmt ; format rdi
;         mov rsi, number   ; value rsi

;         xor rax, rax
;         call printf
        
;         ret

%include 'functions.asm'

global main
extern printf

section .data
	negsign             db  '-'
	negsign_len         equ $-negsign
    
    floatfmt            db  '%.6g', 10, 0
    integerfmt          db  '%d', 10, 0

    num1                dq  1.643243

    choice              DB  'y'
    number              DW  12345
    neg_number          DW  -12345
    big_number          DQ  1234567891
    real_number1        DD  1.234
    real_number2        DQ  123.456

    sum DQ 0
    n1 dq 1
    n2 dq 3
    
section .bss
	digitSpace          resb 100
	digitSpacePos       resb 8
    
section .text

main:
    movq xmm0, qword [n1] ; load from memory
    movq xmm1, qword [n2]
    divsd xmm0, xmm1 ; add to itself (double it)
    
    sub rsp,8 ; align stack for print_float
    mov rdi, floatfmt
    mov rax, 1
    call printf
    add rsp,8 ; Clean up stack

    xor eax, eax
    xor edi, edi

    ret ; Done with function




; PRINT FLOAT
    ; sub rsp, 8                  ; allign stack to 16 bytes
    ; movq xmm0, qword [num1]
    ; mov rdi, fmt
    ; mov rax, 1
    ; call printf
    ; add rsp, 8                  ; set stack back 
    ; xor eax, eax
    ; xor edi, edi

    ; ret
;END

; ADD AND PRINT FLOAT
    ; movq xmm0, qword [num1] ; load from memory
    ; addsd xmm0,xmm0 ; add to itself (double it)
    
    ; sub rsp,8 ; align stack for print_float
    ; mov rdi, fmt
    ; mov rax, 1
    ; call printf
    ; add rsp,8 ; Clean up stack

    ; xor eax, eax
    ; xor edi, edi

    ; ret ; Done with function
; END

; ADD NORMAL FROM MEMORY AND PRINT

    ; mov esi, dword [big_number] ; load from memory
    ; mov edi, integerfmt

    ; mov rax, 0
    ; call printf
    
    ; xor edi, edi

    ; ret ; Done with function
; END






; TESTING
    ; add_ints qword [n1], qword [n2], qword [sum]
    ; print_sum qword [sum], integerfmt

    ; sub_ints qword [n1], qword [n2], qword [sum]
    ; print_sum qword [sum], integerfmt

    ; mul_ints qword [n1], qword [n2], qword [sum]
    ; print_sum qword [sum], integerfmt

    ; ret
; END

