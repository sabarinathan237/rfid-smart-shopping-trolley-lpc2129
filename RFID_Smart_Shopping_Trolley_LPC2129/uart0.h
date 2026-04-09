#ifndef UART0_H
#define UART0_H

void uart0_init(void);
void uart0_tx(char ch);
char uart0_rx(void);
void uart0_str(const char *s);

#endif
