/*
 * PasswordHandler.c
 *
 * Created: 09-12-2020 12:21:25
 *  Author: alla1862
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#define passwordLenght 4
int index = 0;
char keyPadInput[passwordLenght];
char password[] = "4444";

void ResetPassword()
{
	memset(keyPadInput, 0, sizeof(keyPadInput));
	index = 0;
}

void CorrectPassword()
{
	PORTH |= (1 << PH5);
	OCR1A = 1800;
	_delay_ms(2000);
	OCR1A = 500;
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
	PORTH &= ~((1 << PH4) | (1 << PH5));
}