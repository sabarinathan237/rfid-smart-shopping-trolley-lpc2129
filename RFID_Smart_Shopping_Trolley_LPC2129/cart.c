#include <string.h>
#include "cart.h"

static CART_ITEM cart[MAX_CART];
static int cart_count = 0;
static int total_bill = 0;
static int last_added_index = -1;

static int find_cart_index(const char *tag)
{
    int i;

    for (i = 0; i < cart_count; i++)
    {
        if (strcmp(cart[i].tag, tag) == 0)
            return i;
    }

    return -1;
}

void cart_init(void)
{
    int i;

    for (i = 0; i < MAX_CART; i++)
    {
        cart[i].tag[0] = '\0';
        cart[i].name[0] = '\0';
        cart[i].price = 0;
        cart[i].qty = 0;
        cart[i].subtotal = 0;
    }

    cart_count = 0;
    total_bill = 0;
    last_added_index = -1;
}

void cart_add_item(PRODUCT *p)
{
    int idx;

    if (p == 0)
        return;

    idx = find_cart_index(p->tag);

    if (idx >= 0)
    {
        cart[idx].qty++;
        cart[idx].subtotal = cart[idx].qty * cart[idx].price;
        last_added_index = idx;
    }
    else
    {
        if (cart_count >= MAX_CART)
            return;

        strcpy(cart[cart_count].tag, p->tag);
        strcpy(cart[cart_count].name, p->name);
        cart[cart_count].price = p->price;
        cart[cart_count].qty = 1;
        cart[cart_count].subtotal = p->price;
        last_added_index = cart_count;
        cart_count++;
    }

    total_bill += p->price;
}

void cart_remove_last(void)
{
    int i;

    if (last_added_index < 0 || cart_count == 0)
        return;

    total_bill -= cart[last_added_index].price;
    cart[last_added_index].qty--;
    cart[last_added_index].subtotal -= cart[last_added_index].price;

    if (cart[last_added_index].qty <= 0)
    {
        for (i = last_added_index; i < cart_count - 1; i++)
        {
            cart[i] = cart[i + 1];
        }

        cart_count--;
        last_added_index = cart_count - 1;
    }

    if (total_bill < 0)
        total_bill = 0;
}

void cart_clear(void)
{
    cart_init();
}

int cart_get_total(void)
{
    return total_bill;
}

int cart_is_empty(void)
{
    return (cart_count == 0);
}
