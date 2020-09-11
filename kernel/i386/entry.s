[ORG 0x00]
[BITS 16]

SECTION .text

jmp 0x1000:START

START:
    mov ax, 0x1000
    mov ds, ax
    mov es, ax

    mov ax, 0x2401
    int 0x15

    jc .A20GATERRORHANDLER
    jmp .A20GATESUCCESS

.A20GATERRORHANDLER:
    in al, 0x92
    or al, 0x02
    and al, 0xFE
    out 0x92, al

.A20GATESUCCESS:
    cli
    lgdt [GDTR]

    mov eax, 0x4000003B ; PG=0, CD=0, NW=0, AM=0, WP=0. NE=1, ET=1, TS=1, EM=0, MP=1, PE=1
    mov cr0, eax

    jmp dword 0x18:(_PROTECTED_MODE - $$ + 0x10000)

[BITS 32]
_PROTECTED_MODE:
    mov ax, 0x20
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ss, ax
    mov esp, 0xFFFE
    mov ebp, 0xFFFE

    push 2
    push 0
    push (successfullySwitchedMessage - $$ + 0x10000)
    call Print
    add esp, 12

    jmp dword 0x18:0x10200

    ret

; Prints Messages x, y
; Param : { string : WORDPTR, x : INT, y : INT }
Print:
	push ebp
	mov ebp, esp
	push eax
	push ecx
	push esi
	push edi

	mov eax, 160
	mul byte [ebp + 16]
	
	add eax, dword [ebp + 12]
	mov edi, eax

	mov esi, dword [ebp + 8]

_PRINT_MESSAGE_LOOP:
	mov cl, byte [esi]

	cmp cl, 0

	je _END_PRINT_MESSAGE_LOOP

	mov byte [edi + 0xB8000], cl

	add si, 1
	add di, 2

	jmp _PRINT_MESSAGE_LOOP

_END_PRINT_MESSAGE_LOOP:
	pop edi
	pop esi
	pop ecx
	pop eax
	pop ebp
	ret


align 8, db 0

dw 0x0000

GDTR:
    dw _GDTEND - GDT - 1
    dd (GDT - $$ + 0x10000)

GDT:
    NULL_DESCRIPTOR:
        dw 0x0000
        dw 0x0000
        db 0x00
        db 0x00
        db 0x00
        db 0x00

    IA_32E_CODE_DESCRIPTOR:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x9A
        db 0xAF
        db 0x00

    IA_32E_DATA_DESCRIPTOR:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x92
        db 0xAF
        db 0x00

    CODE_DESCRIPTOR:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x9A
        db 0xCF
        db 0x00

    DATA_DESCRIPTOR:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x92
        db 0xCF
        db 0x00
_GDTEND:

successfullySwitchedMessage: db "Switched to 32bit Mode", 0

times 512 - ($ - $$) db 0x00