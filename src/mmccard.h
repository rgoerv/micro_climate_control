#ifndef MMCCARD_H_
#define MMCCARD_H_

#define XTAL 8000000L
#define BAUD 9600L								// �������� ������ �������
#define UBRRL_value ( XTAL / ( BAUD * 16 )) - 1 // �������� �������� �������� ������������ �������� ��� �������� UBRR

void timerinit();
void usartinit();
void send_UART(char value); 

void diskinit();

#endif MMCCARD_H_

