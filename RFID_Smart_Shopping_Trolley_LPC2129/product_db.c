#include <string.h>
#include "product_db.h"

static PRODUCT product_db[MAX_PRODUCTS] =
{
    {"49004FA12345", "BOOK",      10},
    {"49004FA67890", "PEN",        5},
    {"49004FA11111", "PENCIL",     3},
    {"49004FA22222", "ERASER",     2},
    {"49004FA33333", "NOTEBOOK",  15},
    {"49004FA44444", "MARKER",    12},
    {"49004FA55555", "SCALE",      8},
    {"49004FA66666", "FILE",      20}
};

int find_product_index(const char *tag)
{
    int i;

    for (i = 0; i < MAX_PRODUCTS; i++)
    {
        if (strcmp(product_db[i].tag, tag) == 0)
            return i;
    }

    return -1;
}

PRODUCT* get_product_by_index(int index)
{
    if (index < 0 || index >= MAX_PRODUCTS)
        return 0;

    return &product_db[index];
}
