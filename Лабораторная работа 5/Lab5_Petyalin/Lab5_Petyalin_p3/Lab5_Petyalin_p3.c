/*
 * Lab5_Petyalin_p3.c
 *
 * Created: 15.10.2025 8:24:50
 * Author : s1250400113
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB = 0xFF & ~(1 << PINB7);
	PORTB |= (1 << PINB7); 
	while(1)
	{
		for(uint8_t i = 0; i < 6; i++)
		{
			// ?????? ????????? PB7 
			if(PINB & (1 << PINB7))
			{
				PORTB = (1 << i);
			}
			else
			{
				PORTB = (0x20 >> i);
			}
			_delay_ms(200);
		}
	}
}

