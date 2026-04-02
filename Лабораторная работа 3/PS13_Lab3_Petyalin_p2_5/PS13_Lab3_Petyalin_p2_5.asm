;
; PS13_Lab3_Petyalin_p2_5.asm
;
; Created: 16.11.2025 20:01:23
; Author : g3rdae
;


reset:
	rjmp main

main:
	ldi r18, 0x00
	out OCR0A, r18
	ldi r19, 0x01
	out OCR0B, r19


loop:
	in r18, OCR0A
	sbrc r18, 0
	ldi r19, 0x00
	out OCR0B, r19
	in r18, OCR0A
	sbrc r18, 0
	nop
	ldi r19, 0xff
	out OCR0B, r19
	in r18, OCR0A
	sbrc r18, 0
	jmp 0x00
	ldi r19, 0x00
	out OCR0B, r19
	rjmp loop
