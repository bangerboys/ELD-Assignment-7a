#include "sounddata.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdint.h>
int c;
ISR(TIMER1_COMPA_vect)
{
	if(c == 23295)
		c = 0;
	else
		OCR2A = pgm_read_byte(&sounddata_data[c]);

	++c;
}

void main()
{
	DDRB |= (1 << 3); // Settting PB3 as output
	TCCR2A |= (1 << WGM21)|(1 << WGM20); //
	TCCR2B &= ~(1 << WGM22);            //    Seeting up PWM mode
	TCCR2A = (TCCR2A | (1 << COM2A1)) & ~(1 << COM2A0); // non inverting PWM on the PWM pin
    TCCR2A &= ~((1 << COM2B1) | (1 << COM2B0));
    TCCR2B = (TCCR2B & ~((1 << CS12) | (1 << CS11))) | (1 << CS10);
    OCR2A = pgm_read_byte(&sounddata_data[0]); // setting pulse width to first c
    cli();
    TCCR1B = (TCCR1B & ~(1 << WGM13)) | (1 << WGM12);
    TCCR1A = TCCR1A & ~((1 << WGM11) | (1 << WGM10));
    TCCR1B = (TCCR1B & ~((1 << CS12) | (1 << CS11))) | (1 << CS10);
    OCR1A = 2000; // setting the value of OCR1A - compare register
    TIMSK1 |= (1 << OCIE1A); // Interrupt enabled
    c = 0;
    sei();
	while(1)
	{
	}
}