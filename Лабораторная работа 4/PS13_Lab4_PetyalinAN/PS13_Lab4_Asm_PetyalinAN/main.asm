;
; PS13_Lab4_Asm_PetyalinAN.asm
;
; Created: 10/16/2025 2:28:04 PM
; Author : g3rdae
;


reset:
	rjmp main

main:
	sbi DDRD, PIND3
	cbi DDRD, PIND2
	sbi PORTD, PIND2

loop:
	sbic PIND, PIND2
	rjmp led_off
	sbi PORTD, PIND3 
	rjmp setup_delay

led_off:
	cbi PORTD, PIND3

setup_delay:
	ldi r18, 0x52
	ldi r24, 0x4E
	ldi r25, 0x17

loop_delay:
	subi r18, 0x01
	subi r24, 0x00
	subi r25, 0x00
	brne loop_delay
	rjmp PC+0
	rjmp PC+0
	rjmp PC+0
	rjmp loop