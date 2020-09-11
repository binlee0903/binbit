[ORG 0x00]
[BITS 16]

SECTION .text

jmp 0x07C0:START

START:
	mov ax, 0x07C0
	mov ds, ax

	mov ax, 0xB800
	mov es, ax

	mov ax, 0xFFFE
	mov sp, ax
	mov bp, ax

	mov ax, 0x0000
	mov ss, ax

	mov si, 0
	mov di, 0

_SCREEN_CLEAR_LOOP:
	mov byte [es:di], 0
	mov byte [es:di + 1], 0x0A

	add di, 2

	cmp di, 4000

	jl _SCREEN_CLEAR_LOOP

	mov di, 0

	call ResetDisk

	push 0x1000
	call ReadDisk
	sub sp, 2

	jmp 0x1000:0x0000

_END_SCREEN_CLEAR_LOOP:

; Reset Disk
; Param : None
ResetDisk:
	push bp
	mov bp, sp
	push ax
	push dx

	mov ax, 0
	mov dl, 0
	int 0x13

	jc ErrorHandler

	pop dx
	pop ax
	pop bp
	ret

; Read Floppy Disk
; Param : { Address : WORD }
ReadDisk:
	push bp
	mov bp, sp
	push es
	push ax
	push bx
	push cx
	push ds
	push si
	push di

	mov si, [bp + 4]
	mov es, si

	mov bx, 0x0000
	
	mov di, word [totalSectorCount]

_READ_LOOP:
	cmp di, 0
	je _READ_END
	sub di, 0x01

	mov ah, 0x02	; BIOS Service Number 2(Read Sector)
	mov al, 0x01	; Sector Count To Read

	mov ch, byte [trackNumber]
	mov cl, byte [sectorNumber]

	mov dh, byte [headNumber]
	mov dl, 0x00	; Drive Number

	int 0x13

	jc ErrorHandler

	add si, 0x0020

	mov es, si

	mov al, byte [sectorNumber]
	add al, 0x01
	mov byte [sectorNumber], al
	cmp al, 37
	jl _READ_LOOP
	
	xor byte [headNumber], 0x01
	mov byte [sectorNumber], 0x01

	cmp byte [headNumber], 0x00
	jne _READ_LOOP

	add byte [trackNumber], 0x01
	jmp _READ_LOOP
_READ_END:
	pop di
	pop si
	pop ds
	pop cx
	pop bx
	pop ax
	pop es
	pop bp
	ret

ErrorHandler:

	jmp $

totalSectorCount: dw 1024
kernel_86SectorCount: dw 0x02

trackNumber: db 0x00
sectorNumber: db 0x02
headNumber: db 0x00

times 510 - ($ - $$) db 0x00

db 0x55
db 0xAA