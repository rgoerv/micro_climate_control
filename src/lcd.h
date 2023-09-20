#ifndef LCD_H_
#define LCD_H_

#define LCD_DPRT PORTA
#define LCD_DDDR DDRA
#define LCD_RS 0
#define LCD_EN 1

void lcdcommand(unsigned char cmnd);
void lcddata(unsigned char data);
void lcdinit();
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char *str);
void lcd_clear();

#endif /* LCD_H_ */