/*
 * SmartHus.c
 *
 * Created: 07-12-2020 08:18:22
 * Author : alla1862
 */ 

#include <avr/io.h>

#include <util/delay.h>

int main(void)
{
	DDRB = 0b10000000;
    while (1) 
    {
		if (PINB & (1 << PINB6))
		{
			PORTB |= 0b10000000;
		}
		else
		{
			PORTB &= 0b01111111;
		}
		//_delay_ms(200);
    }
}

