;
; PS13_Lab3_Petyalin_p2_2.asm
;
; Created: 16.11.2025 18:31:16
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
	sbrs r18, 1
	ldi r19, 0x10
	out OCR0B, r19
  	in r18, OCR0A
	sbrs r18, 1
	ldi r19, 0xff
	out OCR0B, r19
	in r18, OCR0A
	sbrs r18, 1
	jmp 0x00
	rjmp loop
