#include "rtc_ds1307.h"
#include "i2c0.h"

#define DS1307_ID  0x68

static unsigned char bcd_to_dec(unsigned char bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

void rtc_get_time(RTC_TIME *t)
{
    i2c0_start();
    i2c0_write(DS1307_ID << 1);
    i2c0_write(0x00);
    i2c0_restart();
    i2c0_write((DS1307_ID << 1) | 1);

    t->sec   = bcd_to_dec(i2c0_read_ack() & 0x7F);
    t->min   = bcd_to_dec(i2c0_read_ack());
    t->hour  = bcd_to_dec(i2c0_read_ack());
    t->day   = bcd_to_dec(i2c0_read_ack());
    t->date  = bcd_to_dec(i2c0_read_ack());
    t->month = bcd_to_dec(i2c0_read_ack());
    t->year  = bcd_to_dec(i2c0_read_nack());

    i2c0_stop();
}
