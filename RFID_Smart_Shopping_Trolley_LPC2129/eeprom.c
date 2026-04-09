#include "eeprom.h"
#include "i2c0.h"
#include "delay.h"

#define EEPROM_ID  0x50

static void eeprom_write_byte(unsigned char dev, unsigned char addr, unsigned char data)
{
    i2c0_start();
    i2c0_write(dev << 1);
    i2c0_write(addr);
    i2c0_write(data);
    i2c0_stop();
    delay_ms(10);
}

static unsigned char eeprom_read_byte(unsigned char dev, unsigned char addr)
{
    unsigned char data;

    i2c0_start();
    i2c0_write(dev << 1);
    i2c0_write(addr);
    i2c0_restart();
    i2c0_write((dev << 1) | 1);
    data = i2c0_read_nack();
    i2c0_stop();

    return data;
}

void eeprom_save_last_bill(int amount)
{
    unsigned char d0, d1, d2, d3;

    d0 = (amount >> 24) & 0xFF;
    d1 = (amount >> 16) & 0xFF;
    d2 = (amount >> 8)  & 0xFF;
    d3 = amount & 0xFF;

    eeprom_write_byte(EEPROM_ID, 0x00, d0);
    eeprom_write_byte(EEPROM_ID, 0x01, d1);
    eeprom_write_byte(EEPROM_ID, 0x02, d2);
    eeprom_write_byte(EEPROM_ID, 0x03, d3);
}

int eeprom_read_last_bill(void)
{
    unsigned char d0, d1, d2, d3;
    int amount;

    d0 = eeprom_read_byte(EEPROM_ID, 0x00);
    d1 = eeprom_read_byte(EEPROM_ID, 0x01);
    d2 = eeprom_read_byte(EEPROM_ID, 0x02);
    d3 = eeprom_read_byte(EEPROM_ID, 0x03);

    amount = ((int)d0 << 24) |
             ((int)d1 << 16) |
             ((int)d2 << 8)  |
             ((int)d3);

    if (amount < 0 || amount > 999999)
        amount = 0;

    return amount;
}
