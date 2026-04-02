/*
 * PS13_PetyalinAN_zadanie_iz_metodichki_variant_71.c
 *
 * Created: 07.03.2026 15:26:49
 * Author : g3rdae
 */ 


#define F_CPU 16000000UL
#define STATE_RUN_TWO 0
#define STATE_RUN_THREE 1
#define STATE_RUN_BOTH_SIDES 2
#define LED_COUNT  19
#define FRAME_RUN_MIN 0x0001
#define FRAME_RUN_MAX 0x40000
#define PORTD_MIN (1 << PIND2)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



volatile uint8_t button_pressed = 0;
volatile uint8_t direction = 0;

void InitPorts();
void InitINT();

int main(void)
{
    //?????????? ? ??????
	InitPorts();
	InitINT();
	
	sei();
	
	uint32_t frame = 0x0003;
	uint8_t state = 0; //?????????? ??? ???????
	
	
    while (1) 
    {
		// ????????? ?????? (???????????? ???????)
		if (button_pressed)
		{
			button_pressed = 0;
			if (state == STATE_RUN_TWO)
			{
				frame = 0x0007;
			}
			if (state == STATE_RUN_THREE)
			{
				frame = 0x0001;
			}
			state++;
			if (state > STATE_RUN_BOTH_SIDES)
			{
				state = 0;
				frame = 0x0003;
			}
			
			
		}
		// ????????? ?????
		switch(state)
		{
			case STATE_RUN_TWO:
				frame <<= 1;
				
				if (frame > 0x7FFFF)
				{
					frame = 0x0003;
				}
				
			break;
			
			case STATE_RUN_THREE:
				frame <<= 1;
				
				if (frame > 0x7FFFF)
				{
					frame = 0x0007;
				}
			
			break;
			
			case STATE_RUN_BOTH_SIDES:
				if (direction == 0)
				{  
					frame <<= 1;
					
					if (frame > FRAME_RUN_MAX)
					{
						frame = FRAME_RUN_MAX;
						direction = 1;
					}
				}
				else
				{
					frame >>= 1;
					if (frame <= FRAME_RUN_MIN)
					{
						frame = FRAME_RUN_MIN;
						direction = 0;
					}
				}
				
			
			break;
			
			default:break;
		}
		// ????? ?????
		PORTB = frame;// C????????? PORTB 0-5
		
		PORTD = PORTD_MIN;
		PORTD |= (frame >> 6) & 0x03 ; //?????????? PORTD 6-7
		PORTD |= (frame >> 5) & 0xF8 ; //?????????? PORTD 8-12
		
		PORTC = frame >> 13;// ?????????? PORTC 
		// ????????
		_delay_ms(300);
    }
	
	
}

ISR(INT0_vect)
{
	button_pressed = 1;
}

void InitPorts()
{
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = (0xFF) & ~(1 << PIND2);
}

void InitINT()
{
	DDRD &= ~(1 << PIND2);
	PORTD |= (1 << PIND2);
	EIMSK |= (1 << INT0); // ???????? INT0 (??? ??????)
	EICRA |= (1 << ISC01); // ?????????? ?? ?????????? ?????? INT0
}
