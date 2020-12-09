/*
 * KeyPad.c
 *
 * Created: 07-12-2020 13:10:28
 *  Author: alla1862
 */ 

#include <avr/io.h>

void ColumnScan()
{
	static int columnCounter = 1;			// Value 1 - 4 represents selected Column
	
	char portBuffer = PORTK & 0b11110000;	// Prevents glitches in bit manipulation, clear all column bits
	
	switch (columnCounter)
	{
		case 1:
		portBuffer |= 0b00000111;			// reset C1
		PORTK = portBuffer;
		break;
		case 2:
		portBuffer |= 0b00001011;			// reset C2
		PORTK = portBuffer;
		break;
		case 3:
		portBuffer |= 0b00001101;			// reset C3
		PORTK = portBuffer;
		break;
		case 4:
		portBuffer |= 0b00001110;			// reset C4
		PORTK = portBuffer;
		break;
	}
	columnCounter++;
	if (columnCounter > 4)
	{
		columnCounter = 1;					// Reset back to first Column
	}
}



char DecodeKey(char data)
{
	char key;
	switch (data)
	{
		case 0b01110111: key = '1'; break;
		case 0b10110111: key = '4'; break;
		case 0b11010111: key = '7'; break;
		case 0b11100111: key = '*'; break;
		case 0b01111011: key = '2'; break;
		case 0b10111011: key = '5'; break;
		case 0b11011011: key = '8'; break;
		case 0b11101011: key = '0'; break;
		case 0b01111101: key = '3'; break;
		case 0b10111101: key = '6'; break;
		case 0b11011101: key = '9'; break;
		case 0b11101101: key = '#'; break;
		case 0b01111110: key = 'A'; break;
		case 0b10111110: key = 'B'; break;
		case 0b11011110: key = 'C'; break;
		case 0b11101110: key = 'D'; break;
		default:         key = '.'; break;
	}
	return key;
}

char ReadRows()
{
	char pinRead = PINK;
	if (pinRead < 0xF0)			// test for a row line going low
	{
		return DecodeKey(pinRead);
	}
	return '.';
}