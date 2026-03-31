/*
 * PS13_Lab8_PetyalinAN_p1.c
 *
 * Created: 06.01.2026 13:10:42
 * Author : g3rdae
 */ 

#define F_CPU 16000000UL
#define D4 PINB0
#define D5 PINB1
#define D6 PINB2
#define D7 PINB3
#define RS PINB5
#define RW PINB6
#define PD2 PIND2
#define E PINB7
#define CMD 0
#define DATA 1

#define INIT PORTB &= ~(1 << RS); PORTB = (0x30 >> 4);PORTB |= (1 << E);asm("nop");asm("nop");asm("nop");PORTB &= ~(1 << E);PORTB = 0;
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
uint8_t segments[] = {
	// GFEDCBA
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
void InitPorts(void);
void InitTimer1(void);
void Bin2Dec(uint16_t data);
void InitADC(void);
void InitUSART(void);
void SendString(char* buffer);
void SendChar(char symbol);
void InitLCD(void);
void LCD_Write(uint8_t type,char data);
char LCD_Read(void);
volatile uint8_t bcd_buffer[] = {0,0,0,0};
volatile uint16_t display_val = 0;
int main(void)
{
	InitPorts();
	InitTimer1();
	EIMSK |= (1 << INT0);  //Enable INT0
	EICRA |= (1 << ISC01); //Trigger on falling edge of INT0
	InitLCD();
	InitADC();
	InitUSART();
	sei();
	//global interrupt enable
	PORTB &= ~(1 << PINB0); //OE = low (active)
	SendString("Hello\r\n");
	LCD_Write(DATA,'H');
	LCD_Write(DATA,'e');
	LCD_Write(DATA,'l');
	LCD_Write(DATA,'l');
	LCD_Write(DATA,'o');
	LCD_Write(CMD,0x40|0x80); // ??????? ?? ?????? ??????
	LCD_Write(DATA,'V');
	LCD_Write(DATA,'a');
	LCD_Write(DATA,'l');
	LCD_Write(DATA,'u');
	LCD_Write(DATA,'e');
	LCD_Write(DATA,'=');
	LCD_Write(DATA,0x20); // ????? ???????
	while(1)
	{
		Bin2Dec(ADC);
		LCD_Write(CMD, 0x47 | 0x80); //????????? ??????? ?? 7-?
								  //?????????? 2-? ??????
		LCD_Write(DATA, 0x30+bcd_buffer[3]);
		LCD_Write(DATA, 0x30+bcd_buffer[2]);
		LCD_Write(DATA, 0x30+bcd_buffer[1]);
		LCD_Write(DATA, 0x30+bcd_buffer[0]);
	}
}
//--------------------------------------------
ISR(TIMER1_COMPB_vect){
}
ISR(INT0_vect){
	SendString("Value = ");
	SendChar(0x30 + bcd_buffer[3]);
	SendChar(0x30 + bcd_buffer[2]);
	SendChar(0x30 + bcd_buffer[1]);
	SendChar(0x30 + bcd_buffer[0]);
	SendString("\r\n");
}
ISR(USART_RX_vect){
	if(UDR0 == 0x20)
	{
		SendString("It was SPACE button\r\n");
	}
}
ISR(ADC_vect){
	display_val = ADC;
}
//--------------------------------------------
void InitPorts(void){
	DDRB = 0Xff;
	PORTB = 0;
	DDRD = (0<<PD2);
	PORTD |= (1<<PD2);
}
void InitTimer1( void){
	TCCR1A = 0;
	TCCR1B = (1<<CS11 | 1<<CS10 | 1<<WGM12);
	TCNT1 = 0;
	TIMSK1 |= (1<<OCIE1B);
	OCR1A = 24992; 
	OCR1B = 24992;
}
void Bin2Dec(uint16_t data){
	bcd_buffer[3] = (uint8_t)(data/1000);
	data = data % 1000;
	bcd_buffer[2] = (uint8_t)(data/100);
	data = data % 100;
	bcd_buffer[1] = (uint8_t)(data/10);
	data = data % 10;
	bcd_buffer[0] = (uint8_t)(data);
}
void InitADC( void){
	ADMUX = (1<<MUX0);
	ADCSRB = (1<<ADTS2 | 1<<ADTS0);
	ADCSRA = (1<<ADEN | 1<<ADATE | 1<<ADIE);
}
void InitUSART(){
	UCSR0B = (1<<RXEN0 | 1<<TXEN0 | 1<<RXCIE0);
	UCSR0C = (1<<UCSZ01 | 1<<UCSZ00);
	UBRR0H = 0;
	UBRR0L = 0x0C;
}
void SendChar(char symbol){
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = symbol;
}
void SendString(char * buffer){
	while(*buffer != 0){
		SendChar(*buffer++);
	}
}
void InitLCD(void)
{
	uint8_t BF = 0x80;
	_delay_ms(40);
	INIT;
	_delay_ms(5);
	INIT;
	_delay_us(150);
	INIT;
	_delay_ms(5);
	do
	{
		BF = (0x80 & LCD_Read());
	}while(BF == 0x80);
	PORTB &= ~(1 << RS);
	PORTB = (0x20 >> 4);
	PORTB |= (1 << E);
	asm("nop");
	asm("nop");
	asm("nop");
	PORTB &= ~(1 << E);
	PORTB = 0;
	do
	{
		BF = (0x80 & LCD_Read());
	}while(BF == 0x80);
	LCD_Write(CMD, 0x28);
	LCD_Write(CMD, 0x0C);
	LCD_Write(CMD, 0x06);
}
void LCD_Write(uint8_t type, char data){
	uint8_t BF = 0x80;
	do
	{
		BF = (0x80 & LCD_Read());
	}while(BF == 0x80);
	PORTB |= (type << RS);
	PORTB |= (1 << E);
	PORTB &= ~(0x0F);
	PORTB |= (0x0F & (data >> 4));
	PORTB &= ~(1 << E);
	asm("nop");
	asm("nop");
	asm("nop");
	PORTB |= (1 << E);
	PORTB &= ~(0x0F);
	PORTB |= (0x0F & data);
	PORTB &= ~(1 << E);
	PORTB = 0;
}
char LCD_Read(void)
{
	char retval = 0;
	PORTB &= ~(1 << RS);
	PORTB |= (1 << RW);
	DDRB &= ~(1 << D4 | 1 << D5 | 1 << D6 | 1 << D7);
	PORTB |= (1 << E);
	asm("nop");
	asm("nop");
	retval = (PINB & 0x0F) << 4;
	PORTB &= ~(1 << E);
	asm("nop");
	asm("nop");
	asm("nop");
	PORTB |= (1 << E);
	asm("nop");
	asm("nop");
	retval |= (PINB & 0x0F);
	PORTB &= ~(1 << E);
	DDRB |= (1 << D4 | 1 << D5 | 1 << D6 | 1 << D7);
	PORTB = 0;
	return retval;
}