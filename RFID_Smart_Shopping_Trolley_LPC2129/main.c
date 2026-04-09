#include <lpc21xx.h>
#include <string.h>
#include "delay.h"
#include "lcd.h"
#include "uart0.h"
#include "rfid.h"
#include "i2c0.h"
#include "eeprom.h"
#include "rtc_ds1307.h"
#include "product_db.h"
#include "cart.h"

#define SW_REMOVE      (1 << 14)
#define SW_CHECKOUT    (1 << 15)
#define SW_CLEAR       (1 << 16)

static void gpio_init(void);
static void system_init(void);
static void welcome_screen(void);
static void show_last_bill_screen(void);
static void show_ready_screen(void);
static void show_total_screen(void);
static void show_invalid_tag_screen(void);
static void show_checkout_screen(void);
static void handle_rfid_scan(void);
static void handle_remove_switch(void);
static void handle_clear_switch(void);
static void handle_checkout_switch(void);
static void lcd_print_2digit(unsigned int n);

int main(void)
{
    system_init();

    welcome_screen();
    show_last_bill_screen();
    show_ready_screen();

    while (1)
    {
        handle_remove_switch();
        handle_clear_switch();
        handle_checkout_switch();
        handle_rfid_scan();
    }
}

static void gpio_init(void)
{
    IODIR0 &= ~(SW_REMOVE | SW_CHECKOUT | SW_CLEAR);
}

static void system_init(void)
{
    gpio_init();
    lcd_init();
    uart0_init();
    i2c0_init();
    rfid_init();
    cart_init();
}

static void welcome_screen(void)
{
    lcd_clear();
    lcd_goto(0x80);
    lcd_str("SMART SHOPPING");
    lcd_goto(0xC0);
    lcd_str("TROLLEY SYSTEM");
    delay_sec(2);
}

static void show_last_bill_screen(void)
{
    int last_bill;

    last_bill = eeprom_read_last_bill();

    lcd_clear();
    lcd_goto(0x80);
    lcd_str("LAST BILL:");
    lcd_goto(0xC0);
    lcd_str("Rs ");
    lcd_int(last_bill);
    delay_sec(2);
}

static void show_ready_screen(void)
{
    lcd_clear();
    lcd_goto(0x80);
    lcd_str("SCAN RFID TAG");
    lcd_goto(0xC0);
    lcd_str("Rmv Clr Chk");
}

static void show_total_screen(void)
{
    lcd_clear();
    lcd_goto(0x80);
    lcd_str("TOTAL: Rs ");
    lcd_int(cart_get_total());
    lcd_goto(0xC0);
    lcd_str("Rmv Clr Chk");
}

static void show_invalid_tag_screen(void)
{
    lcd_clear();
    lcd_goto(0x80);
    lcd_str("UNKNOWN ITEM");
    lcd_goto(0xC0);
    lcd_str("TRY AGAIN");
    delay_sec(2);
    show_ready_screen();
}

static void show_checkout_screen(void)
{
    RTC_TIME t;
    int total;

    total = cart_get_total();
    rtc_get_time(&t);

    lcd_clear();
    lcd_goto(0x80);
    lcd_str("TOTAL: Rs ");
    lcd_int(total);
    delay_sec(2);

    lcd_clear();
    lcd_goto(0x80);
    lcd_print_2digit(t.date);
    lcd_data('/');
    lcd_print_2digit(t.month);
    lcd_data('/');
    lcd_print_2digit(t.year);

    lcd_goto(0xC0);
    lcd_print_2digit(t.hour);
    lcd_data(':');
    lcd_print_2digit(t.min);
    lcd_data(':');
    lcd_print_2digit(t.sec);

    delay_sec(3);

    lcd_clear();
    lcd_goto(0x80);
    lcd_str("THANK YOU");
    lcd_goto(0xC0);
    lcd_str("VISIT AGAIN");
    delay_sec(2);
}

static void handle_rfid_scan(void)
{
    char tag[13];
    int product_index;
    PRODUCT *p;

    rfid_read_tag(tag);

    if (strlen(tag) == 0)
        return;

    product_index = find_product_index(tag);

    if (product_index >= 0)
    {
        p = get_product_by_index(product_index);

        cart_add_item(p);

        lcd_clear();
        lcd_goto(0x80);
        lcd_str("ITEM:");
        lcd_str(p->name);

        lcd_goto(0xC0);
        lcd_str("PRICE: Rs ");
        lcd_int(p->price);

        delay_sec(2);
        show_total_screen();
    }
    else
    {
        show_invalid_tag_screen();
    }
}

static void handle_remove_switch(void)
{
    if ((IOPIN0 & SW_REMOVE) == 0)
    {
        delay_ms(200);

        if ((IOPIN0 & SW_REMOVE) == 0)
        {
            if (cart_is_empty())
            {
                lcd_clear();
                lcd_goto(0x80);
                lcd_str("CART EMPTY");
                lcd_goto(0xC0);
                lcd_str("NOTHING REMOVE");
                delay_sec(2);
            }
            else
            {
                cart_remove_last();

                lcd_clear();
                lcd_goto(0x80);
                lcd_str("LAST ITEM");
                lcd_goto(0xC0);
                lcd_str("REMOVED");
                delay_sec(2);
            }

            while ((IOPIN0 & SW_REMOVE) == 0);
            show_total_screen();
        }
    }
}

static void handle_clear_switch(void)
{
    if ((IOPIN0 & SW_CLEAR) == 0)
    {
        delay_ms(200);

        if ((IOPIN0 & SW_CLEAR) == 0)
        {
            cart_clear();

            lcd_clear();
            lcd_goto(0x80);
            lcd_str("CART CLEARED");
            lcd_goto(0xC0);
            lcd_str("TOTAL: Rs 0");
            delay_sec(2);

            while ((IOPIN0 & SW_CLEAR) == 0);
            show_ready_screen();
        }
    }
}

static void handle_checkout_switch(void)
{
    int total;

    if ((IOPIN0 & SW_CHECKOUT) == 0)
    {
        delay_ms(200);

        if ((IOPIN0 & SW_CHECKOUT) == 0)
        {
            total = cart_get_total();

            if (total <= 0)
            {
                lcd_clear();
                lcd_goto(0x80);
                lcd_str("NO ITEMS IN");
                lcd_goto(0xC0);
                lcd_str("THE CART");
                delay_sec(2);
            }
            else
            {
                eeprom_save_last_bill(total);
                show_checkout_screen();
                cart_clear();
            }

            while ((IOPIN0 & SW_CHECKOUT) == 0);
            show_ready_screen();
        }
    }
}

static void lcd_print_2digit(unsigned int n)
{
    lcd_data((n / 10) + '0');
    lcd_data((n % 10) + '0');
}
