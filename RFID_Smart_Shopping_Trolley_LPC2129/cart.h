#ifndef CART_H
#define CART_H

#include "product_db.h"

#define MAX_CART  8

typedef struct
{
    char tag[TAG_LEN];
    char name[20];
    int price;
    int qty;
    int subtotal;
} CART_ITEM;

void cart_init(void);
void cart_add_item(PRODUCT *p);
void cart_remove_last(void);
void cart_clear(void);
int cart_get_total(void);
int cart_is_empty(void);

#endif
