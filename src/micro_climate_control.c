#include "dht.h"
#include "lcd.h"
#include "mmccard.h"

#include <mega128.h>

#include <io.h>
#include <pgmspace.h>
#include <delay.h>
#include <sdcard.h>

unsigned char humi[5];
unsigned char temp[5];
unsigned char* n = "\n";
	
void setup(void)
{
	DDRA  = 0x00;
	PORTA = 0x00;
	
	DDRC  = 0xff;
	PORTC = 0x00;
	DDRB  = 0xff;
	PORTB = 0x00;
	DDRD  = 0xff;
	PORTD = 0x00;

	PORTE |= 0x80; // from buzzer
	
	lcdinit();		/* initialize LCD */
	lcd_clear();    /* clear LCD */
		
	timerinit();	/* initialize timer */
	diskinit();
	usartinit();

	delay_ms(100);
}


void main (void)
{
	setup();
	lcd_gotoxy(0, 0);
	lcd_print("Humidity =");
	lcd_gotoxy(0, 1);
	lcd_print("Temp = ");
	delay_ms(500);
	
	while(1)
	{
		DHT_Process(humi, temp);
		disk_write(0, humi, 0, 1);
		disk_write(0, n, 0, 1);
		disk_write(0, temp, 0, 1);
		disk_write(0, n, 0, 1);
		delay_ms(500);
	}
}

interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
	disk_timerproc();	// ����� ������� �������������
}