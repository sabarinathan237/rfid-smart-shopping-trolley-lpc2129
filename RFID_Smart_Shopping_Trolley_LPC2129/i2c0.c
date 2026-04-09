#include <lpc21xx.h>
#include "i2c0.h"

#define PCLK      15000000
#define LOADVAL   ((PCLK/100000)/2)

void i2c0_init(void)
{
    PINSEL0 &= ~0x000000F0;
    PINSEL0 |=  0x00000050;   /* P0.2=SCL0, P0.3=SDA0 */

    I2SCLL = LOADVAL;
    I2SCLH = LOADVAL;
    I2CONSET = (1 << 6);
}

void i2c0_start(void)
{
    I2CONSET = (1 << 5);
    while ((I2CONSET & (1 << 3)) == 0);
    I2CONCLR = (1 << 5);
}

void i2c0_restart(void)
{
    I2CONSET = (1 << 5);
    I2CONCLR = (1 << 3);
    while ((I2CONSET & (1 << 3)) == 0);
    I2CONCLR = (1 << 5);
}

void i2c0_stop(void)
{
    I2CONSET = (1 << 4);
    I2CONCLR = (1 << 3);
}

void i2c0_write(unsigned char data)
{
    I2DAT = data;
    I2CONCLR = (1 << 3);
    while ((I2CONSET & (1 << 3)) == 0);
}

unsigned char i2c0_read_ack(void)
{
    I2CONSET = (1 << 2);
    I2CONCLR = (1 << 3);
    while ((I2CONSET & (1 << 3)) == 0);
    return I2DAT;
}

unsigned char i2c0_read_nack(void)
{
    I2CONCLR = (1 << 2);
    I2CONCLR = (1 << 3);
    while ((I2CONSET & (1 << 3)) == 0);
    return I2DAT;
}
