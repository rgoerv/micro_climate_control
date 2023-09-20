#include "dht.h"
#include "lcd.h"

#include <mega128.h>

#include <io.h>
#include <delay.h>
#include <stdlib.h>

unsigned char q;
unsigned char c = 0, I_RH, D_RH, I_Temp, D_Temp, CheckSum;

void Request()						/* Microcontroller send start pulse or request */
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);		/* set to low pin */
	delay_ms(20);					/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN);		/* set to high pin */
}

void Response()						/* receive response from DHT11 */
{
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

unsigned char Receive_data()							/* receive data */
{
	for (q = 0; q < 8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0);	/* check received bit 0 or 1 */
		delay_us(30);
		if(PIND & (1<<DHT11_PIN))				/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);						/* then its logic HIGH */
		else									/* otherwise its logic LOW */
		c = (c<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}

void DHT_Process(unsigned char* humi, unsigned char* temp)
{
	char data[5];
	
	Request();				/* send start pulse */
	Response();				/* receive response */
	I_RH=Receive_data();	/* store first eight bit in I_RH */
	D_RH=Receive_data();	/* store next eight bit in D_RH */
	I_Temp=Receive_data();	/* store next eight bit in I_Temp */
	D_Temp=Receive_data();	/* store next eight bit in D_Temp */
	CheckSum=Receive_data();/* store next eight bit in CheckSum */
	
	if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
	{
		lcd_gotoxy(0,0);
		lcd_print("Error");
	}
	else
	{
		itoa(I_RH, data);
		lcd_gotoxy(11, 0);
		lcd_print(data);
		lcd_print(".");
		humi = data;
		
		itoa(D_RH, data);
		lcd_print(data);
		lcd_print("%");

		itoa(I_Temp, data);
		lcd_gotoxy(6, 1);
		lcd_print(data);
		lcd_print(".");
		temp = data;
		
		itoa(D_Temp, data);
		lcd_print(data);
		lcddata(0xDF);
		lcd_print("C ");
		
		itoa(CheckSum, data);
		lcd_print(data);
		lcd_print(" ");
		
		if(I_Temp > 40)
		{
			delay_ms(1000);
			PORTE &= ~(1 << PORTE7);
			delay_ms(10000);
			PORTE |= 1 << PORTE7;
			delay_ms(1000);
			PORTE &= ~(1 << PORTE7);
			delay_ms(1000);
			PORTE |= 1 << PORTE7;
			delay_ms(1000);
			PORTE &= ~(1 << PORTE7);
			
		}
	}
}