#ifndef PRODUCT_DB_H
#define PRODUCT_DB_H

#define MAX_PRODUCTS  8
#define TAG_LEN       13

typedef struct
{
    char tag[TAG_LEN];
    char name[20];
    int price;
} PRODUCT;

int find_product_index(const char *tag);
PRODUCT* get_product_by_index(int index);

#endif
