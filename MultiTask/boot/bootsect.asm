
%define    BASE    0x100
%define KSIZE    30

[BITS 16]
[ORG 0x0]

jmp start

%include "UTIL.INC"
%include "GDT.INC"

start:

; segmento 0x07C0 inicializacija
    mov ax, 0x07C0
    mov ds, ax
    mov es, ax
    mov ax, 0x8000    ; stack in 0xFFFF
    mov ss, ax
    mov sp, 0xf000

; boot paemimas
    mov [bootdrv], dl    

; pranesimo parodymas
    mov si, msgStart
    call display

; pakrauti kerneli
    xor ax, ax
    int 0x13

    push es
    mov ax, BASE
    mov es, ax
    mov bx, 0
    
    mov ah, 2
    mov al, KSIZE
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [bootdrv]
    int 0x13
    pop es


;  GDT inicializavimas
    ; descInit base(32), limit(20/32), acces/type(8), flags(4/8), adress(16)
    descInit 0, 0xFFFFF, 10011011b, 1101b, gdt_cs
    descInit 0, 0xFFFFF, 10010011b, 1101b, gdt_ds

; pointerio i GDT inicializavimas
    mov ax, gdtend    ; GDT limito skaiciavimas
    mov bx, gdt
    sub ax, bx
    mov word [gdtptr], ax

    xor eax, eax    ; tiesinio adreso i GDT skaiciavimas
    mov  ax, ds
    mov  bx, gdt
    call calcadr
    mov dword [gdtptr+2], ecx

; perejimas i protected mode
    cli
    lgdt [gdtptr]    ; gdt pakrovimas
    mov eax, cr0
    or   ax, 1
    mov cr0, eax    ; (CR0)

    jmp next
next:
    mov ax, 0x10    ; data segmentas
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x9F000    

    jmp dword 0x8:0x1000

end:
    jmp end


;--------------------------------------------------------------------
msgStart db "loading kernel", 13, 10, 0

gdt:
gdt_null:
    dw 0, 0, 0, 0
gdt_cs:
    dw 0, 0, 0, 0
gdt_ds:
    dw 0, 0, 0, 0
gdtend:

gdtptr:
    dw    0x0000    ; limit
    dd    0         ; base

bootdrv: db 0

;--------------------------------------------------------------------
times 510-($-$$) db 144
dw 0xAA55

