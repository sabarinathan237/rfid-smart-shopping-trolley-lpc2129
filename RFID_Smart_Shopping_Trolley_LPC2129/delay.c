#include <lpc21xx.h>
#include "delay.h"

void delay_ms(unsigned int ms)
{
    T0PR  = 15000 - 1;   /* 1 ms @ 15 MHz PCLK */
    T0TCR = 0x02;
    T0TCR = 0x01;
    while (T0TC < ms);
    T0TCR = 0x00;
    T0TC  = 0;
}

void delay_sec(unsigned int sec)
{
    T0PR  = 15000000 - 1;   /* 1 sec @ 15 MHz PCLK */
    T0TCR = 0x02;
    T0TCR = 0x01;
    while (T0TC < sec);
    T0TCR = 0x00;
    T0TC  = 0;
}
