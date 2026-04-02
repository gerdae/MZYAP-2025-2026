;
; PS13_Lab3_Petyalin_p2_1.asm
;
; Created: 10/15/2025 8:57:15 PM
; Author : g3rdae
;


reset:
	rjmp main

main:
	ldi r18, 0xFF
	ldi r19, 0xFF
	out OCR0A, r18
	out OCR0B, r19
	bset 1

loop:
	in r18, OCR0A
	in r19, OCR0B
	cpc r18, r19
	
	rjmp loop
