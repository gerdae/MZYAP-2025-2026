;
; PS13_Lab3_Petyalin_p1_5.asm
;
; Created: 10/15/2025 8:48:22 PM
; Author : g3rdae
;


reset:
	rjmp main

main:
	ldi r18, 0xFF
	out OCR0A, r18
	bset 2

loop:
	in r18, OCR0A
	lsr r18
	out OCR0A, r18
	
	rjmp loop