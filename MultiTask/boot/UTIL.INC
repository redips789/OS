;---------------------------------------------------------
; Bendrai:	Parodyti string pasibaigianti 0x0
; Pradzia:	ds:si -> rodykle i chain display
;---------------------------------------------------------
display:
	push ax
	push bx
.start:
	lodsb		; ds:si -> al
	cmp al,0	; end chain ?
	jz .end
	mov ah,0x0E	; kvieciam servisa 0x0e, int 0x10 bios interrupt
	mov bx,0x07	; bx -> atributas, al -> ka spausdinam (ascii char)
	int 0x10
        jmp .start

.end:
	pop bx
	pop ax
	ret
