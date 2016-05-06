
;--------------------------------------------------------------------
; CalcAdr
; Pradzia:
;    ax -> segment
;    bx -> offset
; Pabaiga:
;    ecx -> 32 bitu tiesinis adresas
; Pakeitimas: virsutine ebx dalis
;--------------------------------------------------------------------
calcadr:
    xor ecx, ecx
    mov cx, ax
    shl ecx, 4
    and ebx, 0x0000FFFF
    add ecx, ebx
    ret
;--------------------------------------------------------------------


;--------------------------------------------------------------------
; descInit
;--------------------------------------------------------------------
%macro descInit    5    ; base(32), limit(20/32), acces(8), flags(4/8), adress(32)
    push eax
; base :
    mov eax, %1
    mov word [%5+2], ax
    shr eax, 16
    mov byte [%5+4], al
    shr eax, 8
    mov byte [%5+7], al
; limit :
    mov eax, %2
    and eax, 0x000FFFFF
    mov word [%5], ax  ; written (0..15)
    shr eax, 16        ; 
    mov byte [%5+6], 0 ; inicijuojam flags+lim(16..19) i 0
    or  [%5+6], al     ; written (16..19)
; flags :
    mov al, %4
    and al, 0x0F
    shl al, 4
    or [%5+6], al
; acces :
    mov byte [%5+5], %3
    pop eax
%endmacro
;--------------------------------------------------------------------

