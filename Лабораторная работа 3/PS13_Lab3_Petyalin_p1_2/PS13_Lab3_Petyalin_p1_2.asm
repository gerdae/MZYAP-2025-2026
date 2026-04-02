;
; PS13_Lab3_Petyalin_p1_2.asm
;
; Created: 10/15/2025 8:30:10 PM
; Author : g3rdae
;


reset:
	rjmp main
main:
    ldi r18, 0x00
	out OCR0A, r18

loop:
	in r18, OCR0A
	lsl r18
	out OCR0A, r18

	rjmp loop