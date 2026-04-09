#include <lpc21xx.h>
#include "lcd.h"
#include "delay.h"

void lcd_cmd(unsigned char cmd)
{
    IOCLR1 = LCD_D;
    IOCLR1 = LCD_RS;
    IOCLR1 = LCD_RW;

    IOSET1 = (cmd & 0xF0) << 16;
    IOSET1 = LCD_EN;
    delay_ms(2);
    IOCLR1 = LCD_EN;

    IOCLR1 = LCD_D;
    IOSET1 = (cmd & 0x0F) << 20;
    IOSET1 = LCD_EN;
    delay_ms(2);
    IOCLR1 = LCD_EN;
}

void lcd_data(unsigned char data)
{
    IOCLR1 = LCD_D;
    IOSET1 = LCD_RS;
    IOCLR1 = LCD_RW;

    IOSET1 = (data & 0xF0) << 16;
    IOSET1 = LCD_EN;
    delay_ms(2);
    IOCLR1 = LCD_EN;

    IOCLR1 = LCD_D;
    IOSET1 = (data & 0x0F) << 20;
    IOSET1 = LCD_EN;
    delay_ms(2);
    IOCLR1 = LCD_EN;
}

void lcd_str(const char *s)
{
    while (*s)
        lcd_data(*s++);
}

void lcd_int(int n)
{
    char buf[12];
    int i = 0;
    int j;

    if (n == 0)
    {
        lcd_data('0');
        return;
    }

    if (n < 0)
    {
        lcd_data('-');
        n = -n;
    }

    while (n > 0)
    {
        buf[i++] = (n % 10) + '0';
        n /= 10;
    }

    for (j = i - 1; j >= 0; j--)
        lcd_data(buf[j]);
}

void lcd_clear(void)
{
    lcd_cmd(0x01);
}

void lcd_goto(unsigned char pos)
{
    lcd_cmd(pos);
}

void lcd_init(void)
{
    IODIR1 |= LCD_D | LCD_RS | LCD_RW | LCD_EN;
    delay_ms(20);

    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}
