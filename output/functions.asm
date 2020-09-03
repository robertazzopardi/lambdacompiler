%define sys_write 1
%define stdout 1

%define sys_exit 60
%define success 0

%define ascii_off 48
%define nl 10

; call system exit
_exit:
   ; system exit
	mov rax, sys_exit
	mov rdi, success
	syscall

; print function
_printRAX:
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


	; mov rax, -4
	; test rax, rax
	; je _printRAXLoop2
	
	; ;print
	; ; write to console
	; mov rax, sys_write
	; mov rdi, stdout
	
	; mov rsi, num1
	; mov rdx, num1_len 

	; syscall ; call kernal interrupt
	


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