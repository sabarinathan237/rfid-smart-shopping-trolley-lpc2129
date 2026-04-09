#include <lpc21xx.h>
#include "uart0.h"

void uart0_init(void)
{
    PINSEL0 &= ~0x0000000F;
    PINSEL0 |=  0x00000005;   /* P0.0 TXD0, P0.1 RXD0 */

    U0LCR = 0x83;
    U0DLL = 97;               /* ~9600 baud @ 15 MHz */
    U0DLM = 0x00;
    U0LCR = 0x03;
}

void uart0_tx(char ch)
{
    while ((U0LSR & (1 << 5)) == 0);
    U0THR = ch;
}

char uart0_rx(void)
{
    while ((U0LSR & 1) == 0);
    return U0RBR;
}

void uart0_str(const char *s)
{
    while (*s)
        uart0_tx(*s++);
}
