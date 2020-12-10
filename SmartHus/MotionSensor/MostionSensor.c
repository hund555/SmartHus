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
	PCICR |= (1<<PCIE0);
	PCMSK0 |= (1<<PCINT6);
}

void Detected_Motion()
{
	if (!(PINB & (1 << PINB6)))
	{
		PORTB &= 0b01111111;
	}
}