[BITS 32]

global GetCPUID, Execute64bitMode

; Get CPU Identification
; Param : { Read Flag : INT, Result Array : WORDPTR }
GetCPUID:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    push ecx
    push edx
    push esi

    mov eax, dword [ebp + 8]
    cpuid

    mov esi, dword [ebp + 12]

    mov dword [esi], eax
    mov dword [esi + 4], ebx
    mov dword [esi + 8], ecx
    mov dword [esi + 12], edx

    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    pop ebp
    ret

; Execute IA-32e Mode
; Param : { NONE }
Execute64bitMode:
    mov eax, cr4
    or eax, 0x20
    mov cr4, eax

    mov eax, 0x100000
    mov cr3, eax

    mov ecx, 0xC0000080
    rdmsr

    or eax, 0x0100
    wrmsr

    mov eax, cr0
    or eax, 0xE0000000
    xor eax, 0x60000000
    mov cr0, eax

    jmp 0x08:0x200000
