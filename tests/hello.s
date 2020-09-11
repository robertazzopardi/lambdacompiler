%include 'functions.asm'

global main
extern printf

section .data
    sum DQ 0

section .text

main:
; TESTING

    _add 50, 50, qword [sum]
    ; _add qword [n1], qword [n2], qword [sum]
    print_sum qword [sum], integerfmt

    _sub qword [n1], qword [n2], qword [sum]
    print_sum qword [sum], integerfmt

    _mul qword [n1], qword [n2], qword [sum]
    print_sum qword [sum], integerfmt

    _div qword [n1], qword [n2], qword [sum]
    print_float qword [sum], floatfmt

    mov r8, 2
    mov r9, 5
    call _ipow
    mov qword [sum], rax
    print_sum qword [sum], integerfmt

    ret

; END

