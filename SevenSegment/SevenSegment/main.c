#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRA = 0xff; // numeric pin
    DDRE = 0x01; // colon pin
	DDRC = 0x1f; // dig pin
	
	PORTC = 0x1f; // set output
	PORTA = 0x00; // all num led on
	PORTE = 0x01; // colon led off
	
    while (1) 
    {
	    PORTC = 0x11;
		PORTA = 0x89; // H
	    _delay_ms(5);
	    PORTC = 0x12;
	    PORTA = 0x86; // E
	    _delay_ms(5);
	    PORTC = 0x14; 
	    PORTA = 0xc7; // L
	    _delay_ms(5);
	    PORTC = 0x18;
	    PORTA = 0x8c; // P
	    _delay_ms(5);
    }
}

