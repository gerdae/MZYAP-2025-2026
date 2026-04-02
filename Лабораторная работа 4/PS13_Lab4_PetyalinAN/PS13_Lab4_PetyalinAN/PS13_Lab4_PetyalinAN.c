/*
 * PS13_Lab4_PetyalinAN.c
 *
 * Created: 10/16/2025 2:18:51 PM
 * Author : g3rdae
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
	DDRD |= (1 << PIND3);
	DDRD &= ~ (1 << PIND2);
	PORTD |= (1 << PIND2);
	while (1)
	{
		if (PIND & (1 << PIND2))
		PORTD &= ~(1 << PIND3);
		else
		PORTD |= (1 << PIND3);
		_delay_ms(477);
	}
}

