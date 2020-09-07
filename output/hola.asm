; nasm -felf64 hola.asm && gcc -no-pie hola.o && ./a.out
; needed things 
;   wrt ..plt
;   gcc -no-pie
; 

          global    main
        ;   extern    puts
          extern    printf

          section   .text
main:                                       ; This is called by the C library startup code
        ;   mov       rdi, message            ; First integer (or pointer) argument in rdi
        ;   call      puts wrt ..plt                    ; puts(message)
        ;   ret                               ; Return from main back into C library wrapper
        

        
        mov esi, num    ; 64-bit ABI passing order starts w/ edi, esi, ...
        mov edi, fmtd    ;
        mov eax, 0      ; printf is varargs, so EAX counts # of non-integer arguments being passed
        call printf

        ret



fmtd: db "%f", 0x0a, 0

num:	DD	1.234
num2:	DQ	123.456

; msg:    db "Hello, world,", 0

; fmt:    db "%s", 10, 0

; message:
;           dw        'gfdgdf', 10        ; Note strings must be terminated with 0 in C