/*
 * SmartHus.c
 *
 * Created: 07-12-2020 08:18:22
 * Author : alla1862
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "KeyPad/KeyPad.h"
#include "ServoMoter/ServoMoter.h"
#include "PasswordHandler/PasswordHandler.h"


ISR(PCINT0_vect)
{
	PORTB |= 0b10000000;
}

void Init()
{
	DDRK |= 0b00001111;		// Use PortK, upper nibble = input (rows), lower nibble = output (columns)
	PORTK |= 0b11110000;	// Enable Pull-up on Row pins (upper nibble)
	DDRB |= 0b10100000;		// PB7 is for sensor LED PB6 is sensor
	
	DDRH |= (1 << PH4) | (1 << PH5);
	
	Servo_Timer_Init();
}

void Detected_Motion()
{
	if (!(PINB & (1 << PINB6)))
	{
		PORTB &= 0b01111111;
	}
}

int main(void)
{
	Init();
	OCR1A = 500;
	
	//Sensor interrupt
	PCICR |= (1<<PCIE0);
	PCMSK0 |= (1<<PCINT6);
	
	sei();
	
    while (1) 
    {
		ColumnScan();
		char temp = ReadRows();
		//char temp = 5;
		
		if (temp != '.')
		{
			CheckPassword(temp);
		}
		
		Detected_Motion();
    }
}

