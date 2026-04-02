;
; PS13_Lab3_Petyalin_p1_3.asm
;
; Created: 10/15/2025 8:41:12 PM
; Author : g3rdae
;


reset:
	rjmp main
main:
	ldi r18, 0xFF
	ldi r19, 0xFF
	out OCR0A, r18
	out OCR0B, r19
loop:
	in r18, OCR0A
	in r19, OCR0B
	add r18, r19
	out OCR0A, r18
	out OCR0B, r19

	rjmp loop