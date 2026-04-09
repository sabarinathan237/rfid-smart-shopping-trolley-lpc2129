#ifndef LCD_H
#define LCD_H

#include <lpc21xx.h>

#define LCD_D   (0x0F << 20)
#define LCD_RS  (1 << 17)
#define LCD_RW  (1 << 18)
#define LCD_EN  (1 << 19)

void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_str(const char *s);
void lcd_int(int n);
void lcd_clear(void);
void lcd_goto(unsigned char pos);

#endif
