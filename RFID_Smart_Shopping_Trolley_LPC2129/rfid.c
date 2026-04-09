#include <string.h>
#include "uart0.h"
#include "rfid.h"

/*
   EM-18 style reader usually sends 12 ASCII chars.
   This function blocks until 12 chars are received.
*/

void rfid_init(void)
{
    /* UART already initialized in uart0_init() */
}

void rfid_read_tag(char *tag)
{
    unsigned int i;

    for (i = 0; i < 12; i++)
    {
        tag[i] = uart0_rx();
    }

    tag[12] = '\0';
}
