/*
 * Lab2_PS13_PetyalinAN.c
 *
 * Created: 31.03.2026 15:48:20
 * Author : g3rdae
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL

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

