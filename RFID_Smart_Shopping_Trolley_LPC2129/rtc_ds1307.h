#ifndef RTC_DS1307_H
#define RTC_DS1307_H

typedef struct
{
    unsigned char sec;
    unsigned char min;
    unsigned char hour;
    unsigned char day;
    unsigned char date;
    unsigned char month;
    unsigned char year;
} RTC_TIME;

void rtc_get_time(RTC_TIME *t);

#endif
