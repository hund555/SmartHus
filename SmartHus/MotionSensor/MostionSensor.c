/*
 * MostionSensor.c
 *
 * Created: 10-12-2020 08:53:26
 *  Author: alla1862
 */
 #include <avr/io.h>

void MotionSensor_Init()
{
	//Sensor interrupt
	PCICR |= (1<<PCIE0);	//PCIE0 use ISR PCINT0_VECT
	PCMSK0 |= (1<<PCINT6);	//PCINT0-7 are the ones that can use PCINT0_VECT, you can find them on PB0, PB1, PB2, PB3, PB4, PB5, PB6 and PB7.
}

void Detected_Motion()
{
	if (!(PINB & (1 << PINB6)))
	{
		PORTB &= 0b01111111;
	}
}