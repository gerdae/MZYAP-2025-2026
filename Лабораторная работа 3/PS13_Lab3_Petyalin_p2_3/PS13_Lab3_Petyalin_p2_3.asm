;
; PS13_Lab3_Petyalin_p2_3.asm
;
; Created: 16.11.2025 19:01:21
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
	bst r18, 2
	brts 0
	ldi r19, 0xff
	out OCR0B, r19
	clt
	in r18, OCR0A
	bst r18, 1
	brts aftersecondtest

	rjmp loop

aftersecondtest:
	clt
	ldi r19, 0x00
	out OCR0B, r19
	in r18, OCR0A
	bst r18, 1
	brts afterthirdtest
	rjmp loop
	
afterthirdtest:
	ldi r19, 0xff
	out OCR0B, r19
	rjmp loop