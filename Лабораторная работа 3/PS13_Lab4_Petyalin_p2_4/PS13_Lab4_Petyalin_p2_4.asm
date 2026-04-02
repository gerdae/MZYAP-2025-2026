;
; PS13_Lab4_Petyalin_p2_4.asm
;
; Created: 16.11.2025 19:31:10
; Author : g3rdae
;


reset:
	rjmp main

main:
	ldi r18, 0x01
	out OCR0A, r18
	ldi r19, 0x00
	out OCR0B, r19
loop:
	in r18, OCR0A
	inc r18
	brvc afterfirsttest
	rjmp loop

afterfirsttest:
	ldi r19, 0xff
	out OCR0B, r19
	in r18, OCR0A
	inc r18
	brvc aftersecondtest
	ldi r19, 0x00
	out OCR0B, r19
	rjmp loop
	
aftersecondtest:
	rjmp loop