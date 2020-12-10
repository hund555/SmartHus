/*
 * SmartHus.c
 *
 * Created: 07-12-2020 08:18:22
 * Author : alla1862
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "KeyPad/KeyPad.h"
#include "ServoMoter/ServoMoter.h"
#include "PasswordHandler/PasswordHandler.h"
#include "MotionSensor/MotionSensor.h"


ISR(PCINT0_vect)
{
	PORTB |= 0b10000000;
}

void Init()
{
	DDRK |= 0b00001111;		// Use PortK, upper nibble = input (rows), lower nibble = output (columns)
	PORTK |= 0b11110000;	// Enable Pull-up on Row pins (upper nibble)
	DDRB |= 0b10100000;		// PB7 is for sensor LED PB6 is sensor
	
	DDRH |= (1 << PH4) | (1 << PH5); //PH4 red LED turns on if user give the wrong password. PH5 green LED turns on if user give the correct password.
	
	Servo_Timer_Init();
	MotionSensor_Init();
	
	OCR1A = 500;
	
	sei();
}

int main(void)
{
	Init();
	
	
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

