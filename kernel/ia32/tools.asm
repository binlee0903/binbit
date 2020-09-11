[BITS 64]

SECTION .text

global InputPort, OutputPort

; Read 1byte from port
; Param : { Port Number : INT }
InputPort:
    push rdx
    
    mov rdx, rdi
    mov rax, 0
    in al, dx
    
    pop rdx
    ret
    
; Write 1byte to port
; Param : { Port Number : INT, Data : INT }
OutputPort:
    push rdx
    push rax
    
    mov rdx, rdi
    mov rax, rsi
    out dx, al
    
    pop rax
    pop rdx
    ret