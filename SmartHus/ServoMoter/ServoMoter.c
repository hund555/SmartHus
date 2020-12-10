/*
 * ServoMoter.c
 *
 * Created: 09-12-2020 12:17:13
 *  Author: alla1862
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

void Servo_Timer_Init()
{
	// Compare Output Mode: Fast PWM Mode: Clear OC1A on Compare Match, set OC1A at BOTTOM, non-inverting mode (Table 17-5)
	TCCR1A |= (1<<COM1A1);
	
	//Waveform Generation Mode: Mode 8 Fast PWM, Phase and Frequency Correct: WGMn3 = 1 (Table 17-2)
	TCCR1B |= (1 << WGM13);		//non-inverted
	
	// Clock Select Bit: clk/8 prescaling: CS = 011 : = 1, CS11 = 1 (Table 17-6), frekv. = 50Hz
	TCCR1B |= (1<<CS11);
	
	ICR1 = 20000;
}