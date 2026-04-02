;
; PS13_Lab3_Petyalin_p3.asm
;
; Created: 16.11.2025 21:40:34
; Author : g3rdae
;


.set ARR_SIZE = 139

.dseg
arr: .BYTE ARR_SIZE

.cseg

reset:
	rjmp main

main:
	