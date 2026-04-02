/*
 * Lab5_Petyalin_p2.c
 *
 * Created: 15.10.2025 8:20:17
 * Author : s1250400113
 */ 



#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	while(1)
	{
		for( uint8_t i = 0; i < 6; i++)
		{
			PORTB = (1 << i);
			_delay_ms(200);
		}
	}
}

