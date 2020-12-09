/*
 * SmartHus.c
 *
 * Created: 07-12-2020 08:18:22
 * Author : alla1862
 */ 

#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "KeyPad/KeyPad.h"

#define passwordLenght 4

int index = 0;
char keyPadInput[passwordLenght];
char password[] = "4444";

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
	
	// Set output to OC0B = PG5, see datasheet 16.9.4 and Arduino MEGA pin configuration: (pin 4)
	DDRG |= (1<<PG5);
}

void Detected_Motion()
{
	if (!(PINB & (1 << PINB6)))
	{
		PORTB &= 0b01111111;
	}
}

void Servo_Timer_Init()
{
	// Compare Output Mode: Fast PWM Mode: Clear OC0B on Compare Match, set OC0B at BOTTOM, non-inverting mode (Table 16-6)
	TCCR0A |= (1<<COM0B1);					// datasheet 16.9.1
	
	//Waveform Generation Mode: Mode 3 Fast PWM: WGM0 = 1, WGM1 = 1 (Table 16-8)
	TCCR0A |= (1<<WGM00) | (1<<WGM01);
	
	// Clock Select Bit: clk/64 prescaling: CS = 011 : CS01 = 1, CS00 = 1 (Table 16-9), frekv. = 980Hz
	TCCR0B |= (1<<CS01);		// datasheet 16.9.2
	
	
	
}

void ResetPassword()
{
	memset(keyPadInput, 0, sizeof(keyPadInput));
	index = 0;
}

void CorrectPassword()
{
	PORTH |= (1 << PH5);
	OCR0B = (25 * 256) / 100;
	ResetPassword();
}

void WrongPassword()
{
	PORTH |= (1 << PH4);
	ResetPassword();
}

void Append(char input)
{
	keyPadInput[index] = input;
	index++;
}

void CheckPassword(unsigned char userInput)
{
	if (userInput != '*')
	{
		Append(userInput);
	}
	else
	{
		ResetPassword();
	}
	
	if (index != passwordLenght)
	{
	}
	else if (strncmp(password, keyPadInput, 4) == 0)
	{
		CorrectPassword();
	}
	else
	{
		WrongPassword();
	}
	
	_delay_ms(200);
	PORTH &= ~(1 << PH4);
	PORTB &= ~(1 << PB5);
}

int main(void)
{
	Init();
	
	Servo_Timer_Init();
	
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

