/*
 * ServoMotor.c
 *
 * Created: 2022-11-09 오전 12:38:11
 * Author : Hyo
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

/* 16MHz(≈0.0625㎲) */
/* 0.0625㎲ * 64 * ICR3 */

int main(void)
{	
	DDRE = 0x08; // PE3 output
	
	TCCR3A = 0x82; // COM3A1 set, WGM31 set
	TCCR3B = 0x1b; // WGM33, 32 set, CS31, 30 set
	
	ICR3 = 4999; //5000 tick
	
	
	// OCR3A 1 ~ 2ms range => 249 ~ 499
	int startCnt = 149;
	int endCnt = 600;
	
    while (1) 
    {
		for(int i = startCnt; i < endCnt; i++)
		{
			OCR3A = i;
			_delay_ms(10);
		}		
    }
	return 0;
}

