#include "mmccard.h"
#include "lcd.h"

#include <mega128.h>

#include <stdio.h> 
#include <delay.h>
#include <sdcard.h>
#include <io.h>
#include <interrupt.h>

void timerinit()
{
	TCCR1A=0x00;
	TCCR1B=0x0D;
	TCNT1H=0x00;
	TCNT1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x4E;
	TIMSK=0x10;
}

void usartinit()
{
	UBRR0L = UBRRL_value;				// Младшие 8 бит UBRRL_value
	UBRR0H = UBRRL_value >> 8;			// Старшие 8 бит UBRRL_value
	UCSR0B = (1<<TXEN0);					// Бит разрешения передачи
	UCSR0C = (1<< UCSZ00)|(1<< UCSZ01);	// Устанавливаем формат 8 бит данных
}

void send_UART(char value)
{
	while(!( UCSR0A & (1 << UDRE0)));	// Ожидаем когда очистится буфер передачи
	UDR0 = value;						// Помещаем данные в буфер, начинаем передачу
}

void diskinit()
{
	// Проверка подключения карты памяти
	if(disk_initialize(0) == 0)	// Если карта подключена
	{
		lcd_gotoxy(0, 0);
		lcd_print("OK");
		delay_ms(1000);
	} 
	else 
	{
		lcd_gotoxy(0, 0);
		lcd_print("Error connect");
		delay_ms(1000);
	}
}
