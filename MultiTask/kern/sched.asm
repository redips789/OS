
global do_switch

do_switch:
	; Recuper the * current address 
	mov esi, [esp]
	pop eax			; pops @current

	; prepare records
	push dword [esi+4]	; eax
	push dword [esi+8]	; ecx
	push dword [esi+12]	; edx
	push dword [esi+16]	; ebx
	push dword [esi+24]	; ebp
	push dword [esi+28]	; esi
	push dword [esi+32]	; edi
	push dword [esi+48]	; ds
	push dword [esi+50]	; es
	push dword [esi+52]	; fs
	push dword [esi+54]	; gs

	; removes the mask of PIC
	mov al, 0x20
	out 0x20, al

	; load page table
	mov eax, [esi+56]
	mov cr3, eax

	; load records
	pop gs
	pop fs
	pop es
	pop ds
	pop edi
	pop esi
	pop ebp
	pop ebx
	pop edx
	pop ecx
	pop eax

	; return 
	iret

