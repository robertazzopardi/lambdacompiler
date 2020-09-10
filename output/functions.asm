%define sys_write 1
%define stdout 1

%define sys_exit 60
%define success 0

%define ascii_off 48
%define nl 10

; ------------------------------------------------------------------------------
; EXIT PROGRAM
_exit:
    ; system exit
    mov rax, sys_exit
    mov rdi, success
    syscall

; ------------------------------------------------------------------------------
; PRINT FUNCTION
_print:
; test number to see if it is negative -----------------------------------------
    test rax, rax ; check if number is negative 
    jns _not_negative ; jmp if not signed

    mov r8, rax ; store print value

    mov rax, sys_write ; specify system write 
    mov rdi, stdout
    mov rsi, negsign		; output negative sign
    mov rdx, negsign_len	; pass length of negative sign
    syscall ; call kernal interrupt

    mov rax, r8 ; move value back to rax
    neg rax ; change negative value to positive
; test number to see if it is negative end -------------------------------------

_not_negative: ; handle the number normally
    mov rcx, digitSpace
    mov rbx, 10
    mov [rcx], rbx
    inc rcx
    mov [digitSpacePos], rcx

; split into sepetate digits
_printRAXLoop:
    mov rdx, 0
    mov rbx, 10
    div rbx
    push rax
    add rdx, ascii_off

    mov rcx, [digitSpacePos]
    mov [rcx], dl
    inc rcx
    mov [digitSpacePos], rcx

    pop rax
    cmp rax, 0
    jne _printRAXLoop

; print each digit
_printRAXLoop2:
    mov rcx, [digitSpacePos]

    mov rax, 1
    mov rdi, 1
    mov rsi, rcx
    mov rdx, 1
    syscall

    mov rcx, [digitSpacePos]
    dec rcx
    mov [digitSpacePos], rcx

    cmp rcx, digitSpace
    jge _printRAXLoop2

    ret
; ------------------------------------------------------------------------------

%macro add_ints 3
    mov rax,            %1
    mov rbx,            %2
    add rax,            rbx
    mov %3,             rax
    mov rax,            0
%endmacro

%macro sub_ints 3
    mov rax, %1
    mov rbx, %2
    sub rax, rbx
    mov %3, rax
    mov rax, 0
%endmacro

%macro  mul_ints 3
    mov rax, %1
    mov rbx, %2
    mul rbx
    mov %3, rax
    mov rax, 0

%endmacro



%macro print_sum 2
    mov rsi,            %1
    mov rdi,            %2
    mov rax,            0
    call printf
    xor rdi,            rdi
%endmacro