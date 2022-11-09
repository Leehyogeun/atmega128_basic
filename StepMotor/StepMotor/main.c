/*
 * StepMotor.c
 *
 * Created: 2022-11-09 오후 9:42:23
 * Author : Hyo
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/common.h>

unsigned char halfStep[8] = {0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09};
unsigned char fullStep[8] = {0x0c, 0x06, 0x03, 0x09, 0x0c, 0x06, 0x03, 0x09};
unsigned char waveDrive[8] = {0x08, 0x04, 0x02, 0x01, 0x08, 0x04, 0x02, 0x01};
	
/* 16MHz(≈0.0625㎲) */
/* 0.0625㎲ * 64 * 250 */

volatile unsigned char count = 0;
ISR(TIMER1_OVF_vect)
{
	PORTA = halfStep[count];
	count++;
	if(count == 8)
	{
		count = 0;
	}
	TCNT1 = 65285; // 65535 - 250 => 1ms
}

int main(void)
{
	DDRA = 0x0f; // PA0 ~ 3 output
	TCCR1A = 0x00;
	TCCR1B = 0x03;
	TIMSK = 0x04;
	SREG = 0x80; // Global Interrupt Enable
	TCNT1 = 65285;
	
	while (1)
	{
		_delay_ms(10);	
	}
	return 0;
}
/*
#define HALF_MODE_DELAY_MS 1
#define FULL_MODE_DELAY_MS 10

int main(void)
{
	DDRA = 0x0f; // PA0 ~ 3 output
	unsigned char halfStep[8] = {0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09};
	unsigned char fullStep[8] = {0x0c, 0x06, 0x03, 0x09, 0x0c, 0x06, 0x03, 0x09};
	unsigned char waveDrive[8] = {0x08, 0x04, 0x02, 0x01, 0x08, 0x04, 0x02, 0x01};
	unsigned char *testMode;
	
	// check define of delay
	testMode = halfStep;
	
	while (1)
	{
		// for(int i = 7; i >= 0; i--)	// CCW
		for(int i = 0; i < 8; i++)		// CW
		{
			PORTA = testMode[i];
			_delay_ms(HALF_MODE_DELAY_MS);
		}
	}
	return 0;
}
*/