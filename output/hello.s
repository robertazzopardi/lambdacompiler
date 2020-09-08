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


global main
extern printf

section .data
    string db `%f`, 10, 0
    rs dq 1.643243

section .text

main:
; PRINT FLOAT
    sub rsp, 8                  ; allign stack to 16 bytes
    movq xmm0, qword [rs]
    mov rdi, string
    mov rax, 1
    call printf
    add rsp, 8                  ; set stack back 
    xor eax, eax
    xor edi, edi

    ret
