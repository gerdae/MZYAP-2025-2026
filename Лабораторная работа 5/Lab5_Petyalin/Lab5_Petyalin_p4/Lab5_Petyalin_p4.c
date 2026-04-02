/*
 * Lab5_Petyalin_p4.c
 *
 * Created: 15.10.2025 8:26:59
 * Author : s1250400113
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t segments[]=
{
	// ___GFEDCBA
	0b00111111, // 0 - A, B, C, D, E, F
	0b00000110, // 1 - B, C
	0b01011011, // 2 - A, B, D, E, G
	0b01001111, // 3 - A, B, C, D, G
	0b01100110, // 4 - B, C, F, G
	0b01101101, // 5 - A, C, D, F, G
	0b01111101, // 6 - A, C, D, E, F, G
	0b00000111, // 7 - A, B, C
	0b01111111, // 8 - A, B, C, D, E, F, G
	0b01101111, // 9 - A, B, C, D, F, G
};
int main(void)
{
	DDRB = 0xFF; 
	DDRD &= ~(1 << PIND2); 
	PORTD |= (1 << PIND2); 
	uint8_t switch_state = 0;
	uint8_t counter = 0;
	while(1)
	{ 
		if(!(PIND & (1 << PIND2)))
		{
			while((PIND & (1 << PIND2)) == 0); 
			if(switch_state == 0)
			{
				switch_state = 1;
			} 
			else 
			{
				switch_state = 0;
				counter = 0;
			}
		}
		if(switch_state == 0)
		{
			if(counter == 10)
			{
				counter = 0;
			} 
			PORTB = segments[counter++];
			_delay_ms(1000);
		}
	}
}
